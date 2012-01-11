find_package(Boost REQUIRED COMPONENTS unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_BINARY_DIR}/generators)

add_executable(tests TestRunner.cpp MetricFacetList_Tests.cpp FaceData_Tests)

target_link_libraries(tests boost_unit_test_framework-mt generators)
