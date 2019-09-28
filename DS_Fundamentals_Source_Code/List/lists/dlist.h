namespace lists
{
    template<class _Type>
    struct dlist_node
    {
        _Type data;
        dlist_node<_Type>* prev;
        dlist_node<_Type>* next;
    };

    template<class _Type>
    class dlist
    {
    public:
        typedef typename dlist_node<_Type> node_type;
        typedef typename node_type* node_ptr;

    private:
        node_ptr _root;
        node_ptr _end;

    public:

        dlist()
        {
            _root = new node_type();
            _end = new node_type();

            _root->prev = nullptr;
            _root->next = _end;

            _end->prev = _root;
            _end->next = nullptr;
        }

        ~dlist()
        {
            node_ptr current = _root;
            while (current)
            {
                node_ptr next = current->next;
                delete current;
                current = next;
            }

            _root = nullptr;
            _end = nullptr;
        }

        node_ptr begin()
        {
            return _root->next;
        }

        node_ptr end()
        {
            return _end;
        }

        node_ptr rbegin()
        {
            return _end->prev;
        }

        node_ptr rend()
        {
            return _root;
        }

        void push_front(const _Type& value)
        {
            insert_after(_root, value);
        }

        void push_back(const _Type&  value)
        {
            insert_before(_end, value);
        }

        void pop_front()
        {
            remove(_root->next);
        }

        void pop_back()
        {
            remove(_end->prev);
        }

        void insert_before(node_ptr after, const _Type& value)
        {
            // prev <-> after
            // prev <-> node <-> after

            node_ptr node = new node_type();
            node->data = value;
            node->next = after;
            node->prev = after->prev;
            after->prev = node;
            node->prev->next = node;
        }

        void insert_after(node_ptr before, const _Type& value)
        {
            node_ptr node = new node_type();

            // a <-> c
            // a <-> b <-> c 

            node->data = value;

            // b->c
            node->next = before->next;
            
            // a<-b
            node->prev = before;
            
            // a->b
            before->next = node;

            // b<-c
            node->next->prev = node;
        }

        void remove(node_ptr removed)
        {
            node_ptr prev = removed->prev;
            node_ptr next = removed->next;

            prev->next = next;
            next->prev = prev;

            delete removed;
        }
    };
}
