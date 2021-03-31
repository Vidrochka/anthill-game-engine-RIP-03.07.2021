#define BOOST_TEST_MODULE MyTest
#include "../third_party_libs/boost_1_75_0/boost/test/included/unit_test.hpp"

BOOST_AUTO_TEST_CASE(first_test)
{
    int i = 1;
    BOOST_TEST(i);
    BOOST_TEST(i == 2);
}