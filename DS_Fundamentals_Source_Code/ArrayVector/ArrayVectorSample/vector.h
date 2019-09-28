#pragma once

namespace ads 
{
    template<class T>
    class vector
    {
    private:
        const int _initialCapacity = 8;

        T *_data;
        size_t _size;
        size_t _capacity;

    public:

        vector()
        {
            _capacity = _initialCapacity;
            _data = new T[_capacity];
            _size = 0;
        }

        ~vector()
        {
            if (_data)
            {
                delete[] _data;
            }
        }

        // access
        T& operator[](int index)
        {
            return _data[index];
        }


        // capacity
        size_t size() { return _size; }
        size_t capacity() { return _capacity; }

        // modifiers
        void push_back(T& value)
        {
            grow_if_needed();

            _data[_size] = value;
            _size++;
        }

        void push_front(T& value)
        {
            insert_at(0, value);
        }

        // relational operations (==, !=, etc)


    private:
        void insert_at(int index, T& value)
        {
            grow_if_needed();

            // shift everything to the right
            for (int i = _size; i > index; i--)
            {
                _data[i] = _data[i - 1];
            }

            // set the inserted value
            _data[index] = value;
            _size++;
        }

        void grow_if_needed()
        {
            if (_size >= _capacity)
            {
                size_t new_capacity = _capacity * 2;
                T* new_data = new T[new_capacity];
                for (size_t i = 0; i < _capacity; i++)
                {
                    new_data[i] = _data[i];
                }

                delete[] _data;
                _capacity = new_capacity;
                _data = new_data;
            }
        }
    };
}

