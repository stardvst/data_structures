#include <boost/container/vector.hpp>
#include <boost/assign/list_of.hpp>

void boost_vector_sample()
{
    boost::container::vector<int> data;

    data = boost::assign::list_of
        (1)(2)(3)(4)(5)(6)(7)(8)(9)(10);

    int value = data[4];
}