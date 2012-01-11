#include <boost/numeric/ublas/matrix.hpp>
#include <boost/test/unit_test.hpp>

#include "storage_adaptors.hpp"
#include "generators/MetricFacetList.h"

// #include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

BOOST_AUTO_TEST_SUITE(MetricFacetList_Tests)

// checks that an empty matrix is returned for a large negative parameter
// TODO(adrian2005ca): extend the matrix class to have better methods for
// matrix operations
// such as IsEmpty(), IsZero()
BOOST_AUTO_TEST_CASE(HugeNegativeUnderflow) {
  MetricFacetList m(-1000000000);
  matrix<int> computed_matrix = *m.get_facetlist();
  BOOST_CHECK(computed_matrix.size1() == computed_matrix.size2() &&
              computed_matrix.size1() == 0);
}

// checks that tan empty matrix is returned for a small negative parameter
BOOST_AUTO_TEST_CASE(SmallNegativeUnderflow) {
  MetricFacetList m(-1);
  matrix<int> computed_matrix = *m.get_facetlist();
  BOOST_CHECK(computed_matrix.size1() == computed_matrix.size2() &&
              computed_matrix.size1() == 0);
}

// checks that the execption is thrown for 0
BOOST_AUTO_TEST_CASE(ZeroUnderflow) {
  MetricFacetList m(0);
  matrix<int> computed_matrix = *m.get_facetlist();
  BOOST_CHECK(computed_matrix.size1() == computed_matrix.size2() &&
              computed_matrix.size1() == 0);
}

// checks that the execption is thrown for a large positive number
BOOST_AUTO_TEST_CASE(HugeOverflow) {
  MetricFacetList m(1000000000);
  matrix<int> computed_matrix = *m.get_facetlist();
  BOOST_CHECK(computed_matrix.size1() == computed_matrix.size2() &&
              computed_matrix.size1() == 0);
}

// requires the facet list for n = 3
BOOST_AUTO_TEST_CASE(Dimension3FullCheck) {
  MetricFacetList m(3);
  matrix<int> computed_matrix = *m.get_facetlist();

  static const int expectedArray[4][3] = {
    {1 , 1, 1},
    {-1 , 1, 1},
    {1 , -1, 1},
    {1 , 1, -1}
    };
  matrix<int> expected_matrix(4, 3);
  expected_matrix = make_matrix_from_pointer(4, 3, &(expectedArray[0][0]));

  BOOST_REQUIRE(norm_inf(computed_matrix - expected_matrix) == 0);
}

// requires the facet list for n = 4
BOOST_AUTO_TEST_CASE(Dimension4FullCheck) {
  MetricFacetList m(4);
  matrix<int> computed_matrix = *m.get_facetlist();

  static const int expectedArray[16][4] = {
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
  matrix<int> expected_matrix(16, 4);
  expected_matrix = make_matrix_from_pointer(16, 4, &(expectedArray[0][0]));

  BOOST_REQUIRE(norm_inf(computed_matrix - expected_matrix) == 0);
}

// checks the n = 11 facet list size
BOOST_AUTO_TEST_CASE(Dimension11SizeCheck) {
  MetricFacetList m(11);
  matrix<int> computed_matrix = *m.get_facetlist();

  BOOST_CHECK(computed_matrix.size1() == 660 && computed_matrix.size2() == 11);
}

// checks the n = 12 facet list size
BOOST_AUTO_TEST_CASE(Dimension12SizeCheck) {
  MetricFacetList m(12);
  matrix<int> computed_matrix = *m.get_facetlist();

  BOOST_CHECK(computed_matrix.size1() == 880 && computed_matrix.size2() == 12);
}

// checks the n = 100 facet list size
BOOST_AUTO_TEST_CASE(Dimension100SizeCheck) {
  MetricFacetList m(100);
  matrix<int> computed_matrix = *m.get_facetlist();

  BOOST_CHECK(computed_matrix.size1() == 100*99*98*4/6 &&
              computed_matrix.size2() == 100);
}
BOOST_AUTO_TEST_SUITE_END()
