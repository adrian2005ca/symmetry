#include <stdexcept>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/test/unit_test.hpp>

#include "storage_adaptors.hpp"
#include "generators/MetricFacetList.h"

//#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas ;

BOOST_AUTO_TEST_SUITE(MetricFacetList_Tests)

// checks that the execption is thrown for a large negative number
BOOST_AUTO_TEST_CASE(HugeNegativeUnderflow){
  BOOST_CHECK_THROW(MetricFacetList(-1000000000), std::out_of_range);
  }

// checks that the execption is thrown for a small negative number
BOOST_AUTO_TEST_CASE(SmallNegativeUnderflow){
  BOOST_CHECK_THROW(MetricFacetList(-1), std::out_of_range);
  }

// checks that the execption is thrown for 0
BOOST_AUTO_TEST_CASE(ZeroUnderflow){
  BOOST_CHECK_THROW(MetricFacetList(0), std::out_of_range);
  }

// checks that the execption is thrown for MIN_DIMENSION - 1
BOOST_AUTO_TEST_CASE(PositiveUnderflow){
  BOOST_CHECK_THROW(MetricFacetList(2), std::out_of_range);
  }

// checks that the execption is thrown for MAX_DIMENSION + 1
BOOST_AUTO_TEST_CASE(SmallOverflow){
  BOOST_CHECK_THROW(MetricFacetList(13), std::out_of_range);
  }

// checks that the execption is thrown for a large positive number
BOOST_AUTO_TEST_CASE(HugeOverflow){
  BOOST_CHECK_THROW(MetricFacetList(1000000000), std::out_of_range);
  }

//checks the n = 3 facet list
BOOST_AUTO_TEST_CASE(Dimension3FullCheck){
  MetricFacetList m(3);
  matrix<int> computedMatrix = *m.getPointer();

  static const int expectedArray[4][3] ={
    {1 , 1, 1},
    {-1 , 1, 1},
    {1 , -1, 1},
    {1 , 1, -1}
    };
  matrix<int> expectedMatrix(4,3);
  expectedMatrix = make_matrix_from_pointer(4, 3, &(expectedArray[0][0]));

  BOOST_REQUIRE(norm_inf(computedMatrix - expectedMatrix) == 0);

  }

//checks the n = 4 facet list
BOOST_AUTO_TEST_CASE(Dimension4FullCheck){
  MetricFacetList m(4);
  matrix<int> computedMatrix = *m.getPointer();

  static const int expectedArray[16][4] ={
    {1 , 1, 1, 0},
    {-1 , 1, 1, 0},
    {1 , -1, 1, 0},
    {1 , 1, -1, 0},
    {1 , 1, 0, 1},
    {-1 , 1, 0, 1},
    {1 , -1, 0, 1},
    {1 , 1, 0, -1},
    {1 , 0, 1, 1},
    {-1 , 0, 1, 1},
    {1 , 0, -1, 1},
    {1 , 0, 1, -1},
    {0 , 1, 1, 1},
    {0 , -1, 1, 1},
    {0 , 1, -1, 1},
    {0 , 1, 1, -1},
    };
  matrix<int> expectedMatrix(16,4);
  expectedMatrix = make_matrix_from_pointer(16, 4, &(expectedArray[0][0]));

  BOOST_REQUIRE(norm_inf(computedMatrix - expectedMatrix) == 0);

  }

//checks the n = 11 facet list size
BOOST_AUTO_TEST_CASE(Dimension11SizeCheck){
  MetricFacetList m(11);
  matrix<int> computedMatrix = *m.getPointer();

  BOOST_CHECK(computedMatrix.size1() == 660 && computedMatrix.size2() == 11);
  }

//checks the n = 12 facet list size
BOOST_AUTO_TEST_CASE(Dimension12SizeCheck){
  MetricFacetList m(12);
  matrix<int> computedMatrix = *m.getPointer();

  BOOST_CHECK(computedMatrix.size1() == 880 && computedMatrix.size2() == 12);
  }

BOOST_AUTO_TEST_SUITE_END()
