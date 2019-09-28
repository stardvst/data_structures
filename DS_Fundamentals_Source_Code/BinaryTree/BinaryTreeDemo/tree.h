#include <functional>

namespace module5
{
    template<class _Type>
    struct node
    {
        node(const _Type& value)
        {
            data = value;
            left = nullptr;
            right = nullptr;
        }

        _Type data;
        node<_Type> *left;
        node<_Type> *right;
    };

    template<class _Type>
    class bst
    {
        typedef typename node<_Type> node_t;

    private:
        node_t* _root;
        size_t _size;

    public:
        bst()
        {
            _root = nullptr;
            _size = 0;
        }

        ~bst()
        {
            remove_tree(_root);
        }

        size_t size()
        {
            return _size;
        }

        void add(const _Type& value)
        {
            if (_root == nullptr)
            {
                _root = new node_t(value);
            }
            else
            {
                insert_under(_root, value);
            }

            _size++;
        }

        bool contains(const _Type& value)
        {
            return find_node_containing(_root, value) != nullptr;
        }

        void preorder(std::function<void(_Type&)> pred)
        {
            traverse_preorder(_root, pred);
        }

        void postorder(std::function<void(_Type&)> pred)
        {
            traverse_postorder(_root, pred);
        }

        void inorder(std::function<void(_Type&)> pred)
        {
            traverse_inorder(_root, pred);
        }

        bool remove(const _Type& value)
        {
            return remove_value(_root, nullptr, value);
        }

    private:
        bool remove_value(node_t *node, node_t* parent, const _Type& value)
        {
            if (node != nullptr)
            {
                if (node->data == value)
                {
                    remove_node(node, parent);
                    _size--;
                    return true;
                }

                if (value < node->data)
                {
                    return remove_value(node->left, node, value);
                }
                else
                {
                    return remove_value(node->right, node, value);
                }
            }

            return false;
        }

        void remove_leaf(node_t* node, node_t* parent)
        {
            if (parent == nullptr)
            {
                _root = nullptr;
            }
            else
            {
                if (parent->left == node)
                {
                    parent->left = nullptr;
                }
                else
                {
                    parent->right = nullptr;
                }
            }

            delete node;
        }

        void remove_single_child(node_t* node, node_t* parent)
        {
            node_t* child = node->left == nullptr ? node->right : node->left;

            if (parent == nullptr)
            {
                _root = child;
            }
            else
            {
                if (parent->left == node)
                {
                    parent->left = child;
                }
                else
                {
                    parent->right = child;
                }
            }

            delete node;
        }

        void remove_two_children(node_t* node, node_t* parent)
        {
            // pick the least value on the right side
            node_t* replacement = node->right;
            node_t* replacement_parent = nullptr;

            // walk left until the left-most node
            while (replacement->left != nullptr)
            {
                replacement_parent = replacement;
                replacement = replacement->left;
            }

            // if we did any walking update the nodes
            if (replacement_parent != nullptr)
            {
                // move the nodes into their new locations
                // if they are null this will just set
                // nulls as appropriate
                replacement_parent->left = replacement->right;
                replacement->right = node->right;
            }

            // move the delete node's left children into place
            replacement->left = node->left;

            if (parent == nullptr)
            {
                _root = replacement;
            }
            else
            {
                if (node->data < parent->data)
                {
                    parent->left = replacement;
                }
                else
                {
                    parent->right = replacement;
                }
            }

            delete node;
        }

        void remove_node(node_t* node, node_t* parent)
        {
            if (node->left == nullptr && node->right == nullptr)
            {
                // leaf node
                remove_leaf(node, parent);
            }
            else if (node->left != nullptr && node->right != nullptr)
            {
                // two childrne
                remove_two_children(node, parent);
            }
            else
            {
                // must have only one child
                remove_single_child(node, parent);
            }
        }

        void traverse_inorder(node_t* node, std::function<void(_Type&)> pred)
        {
            if (node != nullptr)
            {
                traverse_inorder(node->left, pred);
                pred(node->data);
                traverse_inorder(node->right, pred);
            }
        }

        void traverse_preorder(node_t* node, std::function<void(_Type&)> pred)
        {
            if (node != nullptr)
            {
                pred(node->data);
                traverse_preorder(node->left, pred);
                traverse_preorder(node->right, pred);
            }
        }

        void traverse_postorder(node_t* node, std::function<void(_Type&)> pred)
        {
            if (node != nullptr)
            {
                traverse_postorder(node->left, pred);
                traverse_postorder(node->right, pred);
                pred(node->data);
            }
        }


        node_t* find_node_containing(node_t* node, const _Type& value)
        {
            if (node != nullptr)
            {
                if (node->data == value)
                {
                    return node;
                }

                if (value < node->data)
                {
                    return find_node_containing(node->left, value);
                }
                else
                {
                    return find_node_containing(node->right, value);
                }
            }

            return nullptr;
        }

        void insert_under(node_t* node, const _Type& value)
        {
            if (value < node->data)
            {
                // go to the left
                if (node->left == nullptr)
                {
                    node->left = new node_t(value);
                }
                else
                {
                    return insert_under(node->left, value);
                }
            }
            else
            {
                // go to the right
                if (node->right == nullptr)
                {
                    node->right = new node_t(value);
                }
                else
                {
                    return insert_under(node->right, value);
                }
            }
        }

        void remove_tree(node_t *node)
        {
            if (node != nullptr)
            {
                remove_tree(node->left);
                remove_tree(node->right);
                delete node;
            }
        }
    };
}