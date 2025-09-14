
#include <boost/test/included/unit_test.hpp>

#include "test1.h"

using namespace boost::unit_test;

void free_test_function()
{
  test_types();
  BOOST_TEST( true /* test assertion */ );
}

test_suite* init_unit_test_suite( int /*argc*/, char* /*argv*/[] )
{
  framework::master_test_suite().
    add( BOOST_TEST_CASE( &free_test_function ) );
  return 0;
}