#define BOOST_TEST_MODULE MyTest
#include "P:/boost/2021-03-30/boost_1_75_0/boost/test/included/unit_test.hpp"

BOOST_AUTO_TEST_CASE(first_test)
{
    int i = 1;
    BOOST_TEST(i);
    BOOST_TEST(i == 2);
}