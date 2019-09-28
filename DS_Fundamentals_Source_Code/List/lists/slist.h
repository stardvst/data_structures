namespace lists
{    
    template<class _Type> 
    struct slist_node
    {
        _Type data;
        slist_node<_Type>* next;
    };

    template<class _Type>
    class slist
    {
    public:
        typedef typename slist_node<_Type> node_type;
        typedef typename node_type* node_ptr;

    private:
        node_ptr _root;

    public:

        slist()
        {
            _root = new node_type();
            _root->next = nullptr;
        }

        ~slist()
        {
            while (_root && _root->next)
            {
                remove_after(_root);
            }

            delete _root;

            _root = nullptr;
        }

        node_ptr begin()
        {
            return _root->next;
        }

        node_ptr end()
        {
            return nullptr;
        }

        void push_front(const _Type& value)
        {
            insert_after(_root, value);
        }

        void pop_front()
        {
            remove_after(_root);
        }

        void insert_after(node_ptr node, const _Type& value)
        {
            node_ptr new_node = new node_type();
            new_node->data = value;
            new_node->next = node->next;
            node->next = new_node;
        }

        void remove_after(node_ptr node)
        {
            node_ptr removed = node->next;
            node->next = node->next->next;

            delete removed;
        }

        void reverse()
        {
            node_ptr prev = nullptr, 
                     current = _root->next,
                     next;

            while (current != nullptr)
            {
                next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }

            _root->next = prev;
        }
    };
}