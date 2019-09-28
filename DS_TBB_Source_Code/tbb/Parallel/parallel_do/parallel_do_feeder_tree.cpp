#include "tbb/tbb.h"
#include <list>
#include <atomic>
#include <cassert>

struct tree_node {
    tree_node(int v) : value(v) { }
    int value;
    std::list<tree_node*> children;
};

struct SumTree {
    mutable std::atomic<int> sum = 0;

    void operator()(tree_node *n, tbb::parallel_do_feeder<tree_node*>& feeder) const {
        sum += n->value;
        
        for (tree_node* child : n->children) {
            feeder.add(child);
        }
    }
};

int build_tree(tree_node *root, int immediate_children, int starting_value, int remaining_depth)
{
    int tree_sum = 0;

    if (remaining_depth > 0)
    {
        for (int i = starting_value; i < starting_value + immediate_children; i++)
        {
            tree_sum += i;
            root->children.push_back(new tree_node(i));
        }

        for (tree_node* n : root->children)
        {
            tree_sum += build_tree(n, immediate_children, n->value * 10, remaining_depth - 1);
        }
    }

    return tree_sum;
}

void parallel_do_feeder_tree_sum()
{
/*
                               0
                    1                     2
              10         11         20         21 
           100  101   110  111   200  201   210  211

           sum = 1309
*/
    tree_node root(0);
    int expected = build_tree(&root, 2, 1, 3);

    std::list<tree_node*> root_list = { &root };

    SumTree summer;
    tbb::parallel_do(root_list, summer);

    assert(expected == summer.sum);
}