message(${CMAKE_BINARY_DIR})
cmake_minimum_required(VERSION 2.6)
project(symmetry)

add_subdirectory(containers)
add_subdirectory(generators)
add_subdirectory(tests)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# The version number.
set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)

find_package(Boost REQUIRED)
find_package(Boost REQUIRED COMPONENTS mpi)
include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

find_package(GLPK REQUIRED)
include_directories($(GLPK_INCLUDE_DIRS))

include_directories(${CMAKE_SOURCE_DIR}/containers)
link_directories(${CMAKE_BINARY_DIR}/containers)

include_directories(${CMAKE_SOURCE_DIR}/generators)
link_directories(${CMAKE_BINARY_DIR}/generators)

add_executable(test test.cpp)

target_link_libraries(test containers)
target_link_libraries(test generators)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(doc 
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )

    endif(DOXYGEN_FOUND)
