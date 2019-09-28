#include "tree.h"
#include "treetests.h"
#include <cassert>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
#include <iostream>

using module5::node;
using module5::bst;
using std::string;

namespace treetests
{
    void test_setup()
    {
        srand(time(NULL));
    }

    void test_tree_can_create()
    {
        bst<int> tree;
    }

    void test_tree_can_add()
    {
        bst<int> tree;

        for (int i = 0; i < 100; i++)
        {
            assert(tree.size() == i);
            tree.add(rand());
        }
    }

    void test_tree_can_find()
    {
        bst<int> tree;

        const int test_size = 100;
        int expected[test_size] = { 0 };

        for (int i = 0; i < test_size; i++)
        {
            expected[i] = rand();
            tree.add(expected[i]);
        }

        for (int i = 0; i < test_size; i++)
        {
            assert(tree.contains(expected[i]));
        }
    }

    void test_tree_can_iterate_inorder()
    {
        bst<int> tree;

        std::list<int> expected;

        const int test_size = 100;

        for (int i = 0; i < test_size; i++)
        {
            int add = rand();
            tree.add(add);
            expected.push_front(add);
        }

        expected.sort();

        tree.inorder([&expected](const int& value)
        {
            assert(expected.front() == value);
            expected.pop_front();
        });
    }

    void copy_tree()
    {
        bst<int> tree;
        bst<int> copy;

        for (int i = 0; i < 10; i++)
        {
            tree.add(rand());
        }

        tree.preorder([&copy](const int value) {
            copy.add(value);
        });
    }

    void inorder_print()
    {
        bst<int> tree;

        for (int i = 0; i < 10; i++)
        {
            int add = rand();
            tree.add(add);
        }

        tree.inorder([](const int& value)
        {
            std::cout << value << " ";
        });
    }

    void test_tree_can_iterate_preorder()
    {
        bst<int> tree;

        //        12
        //     9     14
        //  4   11 13  16
        //    5       15

        tree.add(12);
        tree.add(9);
        tree.add(14);
        tree.add(4);
        tree.add(11);
        tree.add(5);
        tree.add(13);
        tree.add(16);
        tree.add(15);

        std::list<int> expected = { 12, 9, 4, 5, 11, 14, 13, 16, 15 };

        tree.preorder([&expected](const int& value)
        {
            assert(expected.front() == value);
            expected.pop_front();
        });
    }

    void test_tree_can_iterate_postorder()
    {
        bst<int> tree;

        //        12
        //     9     14
        //  4   11 13  16
        //    5       15

        tree.add(12);
        tree.add(9);
        tree.add(14);
        tree.add(4);
        tree.add(11);
        tree.add(5);
        tree.add(13);
        tree.add(16);
        tree.add(15);

        std::list<int> expected = { 5, 4, 11, 9, 13, 15, 16, 14, 12 };

        tree.postorder([&expected](const int& value)
        {
            assert(expected.front() == value);
            expected.pop_front();
        });
    }

    void test_tree_can_remove()
    {
        bst<int> tree;

        const int test_size = 1000;
        int expected[test_size] = { 0 };

        for (int i = 0; i < test_size; i++)
        {
            // we're only adding unique values
            int add = rand();
            while (tree.contains(add))
            {
                add = rand();
            }

            expected[i] = add;
            tree.add(expected[i]);
        }

        for (int i = 0; i < test_size; i++)
        {
            assert(tree.contains(expected[i]));
            assert(tree.remove(expected[i]));
            assert(false == tree.contains(expected[i]));
        }
    }

    void test_tree_can_remove2()
    {
        bst<int> tree;

        const int test_size = 1000;
        int expected[test_size] = { 0 };

        for (int i = 0; i < test_size; i++)
        {
            // we're only adding unique values
            int add = rand();
            while (tree.contains(add))
            {
                add = rand();
            }

            expected[i] = add;
            tree.add(expected[i]);
        }

        for (int i = test_size-1; i >= 0; i--)
        {
            assert(tree.contains(expected[i]));
            assert(tree.remove(expected[i]));
            assert(false == tree.contains(expected[i]));
        }
    }



    void test_tree_can_remove_ordered_duplicates()
    {
        bst<int> tree;

        const int test_size = 30000;
        std::list<int> expected;

        for (int i = 0; i < test_size; i++)
        {
            int add = rand();
            expected.push_back(add);
            tree.add(add);
        }

        // everything is in the tree at least twice
        for (int ex : expected)
        {
            tree.add(ex);
        }

        for (int i = test_size - 1; i >= 0; i--)
        {
            int ex = expected.front();

            assert(tree.contains(ex));
            assert(tree.remove(ex));

            // since it was added twice - remove it twice
            assert(tree.contains(ex));
            assert(tree.remove(ex));

            expected.pop_front();
        }

        assert(0 == tree.size());
    }

    void test_tree_remove_root_empty_tree()
    {
        bst<int> tree;
        tree.add(10);

        assert(tree.remove(10));
    }

    void test_tree_remove_root_has_children()
    {
        bst<int> tree;
        tree.add(10);
        tree.add(9);
        tree.add(11);

        assert(tree.remove(10));
        assert(tree.remove(9));
        assert(tree.remove(11));
    }

    void test_tree_remove_child_has_children()
    {
        bst<int> tree;
        tree.add(8);
        tree.add(13);
        tree.add(11);
        tree.add(12);
        tree.add(9);
        tree.add(10);

        assert(tree.remove(11));
    }

    void test_tree_remove_root_has_complex_children()
    {
        bst<int> tree;
        tree.add(8);
        tree.add(13);
        tree.add(11);
        tree.add(12);
        tree.add(9);
        tree.add(10);

        assert(tree.remove(8));
    }

    void test_tree_remove_root_lift_successor()
    {
        bst<int> tree;
        tree.add(8);
        tree.add(13);
        tree.add(11);
        tree.add(12);
        tree.add(9);
        tree.add(10);
        tree.add(7);

        assert(tree.remove(8));
    }

    void manual_nodes()
    {
        node<string> root("root");

        node<string> left("left child");
        root.left = &left;

        node<string> right("right child");
        root.right = &right;
    }

    void test_tree_remove_case_3()
    {
        bst<int> tree;

        //      12
        //   9      17
        //       14
        //         15
        //           16

        tree.add(12);
        tree.add(9);
        tree.add(17);
        tree.add(14);
        tree.add(15);
        tree.add(16);

        tree.remove(12);

        //      14
        //   9      17
        //       15
        //         16
    }


    void run_tests()
    {
        copy_tree();
        inorder_print();
        manual_nodes();
        test_setup();
        test_tree_can_create();
        test_tree_can_add();
        test_tree_can_find();
        test_tree_can_iterate_inorder();
        test_tree_can_iterate_preorder();
        test_tree_can_iterate_postorder();
        test_tree_remove_root_empty_tree();
        test_tree_remove_root_has_children();
        test_tree_remove_child_has_children();
        test_tree_remove_root_has_complex_children();
        test_tree_remove_root_lift_successor();
        test_tree_can_remove();
        test_tree_can_remove2();
        test_tree_remove_case_3();

        for (int i = 0; i < 100; i++)
        {
            test_tree_can_remove_ordered_duplicates();
        }
    }
}