#include "containers/FaceData.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FaceData_Tests)

// checks if default initializer works by checking state.
BOOST_AUTO_TEST_CASE(DefaultConstructor) {
  FaceData face;
  BOOST_CHECK(face.getBin() == 1);
}


BOOST_AUTO_TEST_SUITE_END()
