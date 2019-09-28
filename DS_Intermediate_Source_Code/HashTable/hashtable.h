#include <functional>



template<class KeyType,
         class ValueType,
         class Hash = std::hash<KeyType>>
class hashtable {
private:
    template<class KeyType, class ValueType>
    struct hash_entry {
        KeyType key;
        ValueType value;
        hash_entry *next;

        hash_entry(const KeyType& k, const ValueType& v)
            : key(k), value(v), next(nullptr) { }
    };

    template<class KeyType, class ValueType, class Hash>
    class hashtable_iterator {
        typedef hash_entry<KeyType, ValueType> table_entry;
        size_t current_index;
        table_entry* current_entry;
        hashtable<KeyType, ValueType, Hash> *table;

        table_entry* advance() {
            if (current_entry != nullptr) {
                current_entry = current_entry->next;
            }

            // if we didn't find something then walk the table
            while (current_entry == nullptr && ++current_index < table->capacity) {
                current_entry = table->table[current_index];
            }

            return current_entry;
        }

    public:
        hashtable_iterator(hashtable<KeyType, ValueType, Hash> *table)
            : current_entry(nullptr), current_index(-1) {
            this->table = table;

            if (table != nullptr) {
                advance();
            }
        }

        bool operator==(const hashtable_iterator<KeyType, ValueType, Hash>& iter) const {
            return iter.current_entry == this->current_entry;
        }

        bool operator!=(const hashtable_iterator<KeyType, ValueType, Hash>& iter) const {
            return iter.current_entry != this->current_entry;
        }

        std::pair<KeyType, ValueType> operator*() {
            return std::pair<KeyType, ValueType>(current_entry->key, current_entry->value);
        }

        hashtable_iterator<KeyType, ValueType, Hash>& operator++() {
            advance();
            return *this;
        }
    };

    typedef hash_entry<KeyType, ValueType> entry_t;
    typedef hashtable_iterator<KeyType, ValueType, Hash> iterator_type;

    entry_t** table;
    size_t capacity;
    const double fill_factor = 0.80;
    const double growth_factor = 2.0;
    size_t size;
    Hash hash;

    size_t get_index_for_key(const KeyType& key, size_t table_capacity) {
        return hash(key) % table_capacity;
    }
    
    entry_t** allocate_table(const size_t new_capacity) {
        entry_t** new_table = new entry_t*[new_capacity];
        for (size_t i = 0; i < new_capacity; i++) {
            new_table[i] = nullptr;
        }

        return new_table;
    }

    void rehash_into(entry_t* entry, entry_t** new_table, size_t new_capacity) {
        size_t index = get_index_for_key(entry->key, new_capacity);
        entry->next = new_table[index];
        new_table[index] = entry;
    }

    void rehash_to_new_table(entry_t** old_table, size_t old_capacity, 
                             entry_t** new_table, size_t new_capacity) {
        for (size_t i = 0; i < old_capacity; i++) {
            entry_t* current = old_table[i];
            while (current != nullptr) {
                entry_t* next = current->next;
                current->next = nullptr;
                rehash_into(current, new_table, new_capacity);
                current = next;
            }
        }
    }

    void grow_table() {
        size_t new_capacity = static_cast<size_t>(capacity * growth_factor);
        entry_t** new_table = allocate_table(new_capacity);
        rehash_to_new_table(table, capacity, new_table, new_capacity);
        free_table();

        capacity = new_capacity;
        table = new_table;
    }

    void grow_if_necessary() {
        if ((size + 1) > (capacity * fill_factor)) {
            grow_table();
        }
    }

    ValueType& create_entry(const KeyType& key, ValueType& value) {
        grow_if_necessary();
        entry_t* entry = new entry_t(key, value);
        rehash_into(entry, table, capacity);

        size++;

        return entry->value;
    }

    int remove_key(const KeyType& key) {
        size_t index = get_index_for_key(key, capacity);
        entry_t* current = table[index];

        if (current != nullptr) {
            // first item in chain
            if (current->key == key) {
                table[index] = current->next;
                delete current;
                return 1;
            }

            // subsequent item in chain
            entry_t* previous = current;
            current = current->next;
            while (current) {
                if (current->key == key) {
                    previous->next = current->next;
                    delete current;
                    return 1;
                }

                previous = current;
                current = current->next;
            }
        }

        return 0;
    }

    entry_t* find(const KeyType& key) {
        size_t index = get_index_for_key(key, capacity);
        entry_t* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }

    ValueType& get_or_create(const KeyType& key) {
        entry_t* existing = find(key);
        if (existing != nullptr) {
            return existing->value;
        }

        ValueType value = {};
        return create_entry(key, value);
    }

    void free_all_entries () {
        for (size_t i = 0; i < capacity; i++) {
            entry_t* current = table[i];
            while (current != nullptr) {
                entry_t *next = current->next;
                delete current;
                current = next;
            }
        }
    }

    void free_table() {
        if (table) {
            delete[] table;
            table = nullptr;
        }
    }

public:
    hashtable() {
        size = 0;
        capacity = 4;
        table = allocate_table(capacity);
    }
    
    ~hashtable(){
        free_all_entries();
        free_table();
    }

    ValueType& operator[](const KeyType& key) {
        return get_or_create(key);
    }

    int remove(const KeyType& key) {
        return remove_key(key);
    }

    bool contains(const KeyType& key) {
        return find(key) != nullptr;
    }

    iterator_type begin() {
        return iterator_type(this);
    }

    iterator_type end() {
        return iterator_type(nullptr);
    }
};