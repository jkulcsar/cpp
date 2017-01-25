
cmake_minimum_required(VERSION 2.8)

PROJECT(boost_iostreams_tutorial)

SET(CMAKE_VERBOSE_MAKEFILE ON)

# Boost
FIND_PACKAGE(Boost)
# ...
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# SET(BOOST_LIB_SUFFIX -mt-d)
SET(BOOST_LIB_SUFFIX)
SET(USED_LIBS boost_system${BOOST_LIB_SUFFIX} boost_thread${BOOST_LIB_SUFFIX} boost_regex${BOOST_LIB_SUFFIX})

ADD_DEFINITIONS(-g -Wall -ansi)

add_subdirectory(simple_filter_usage)
add_subdirectory(shell_comments_filter)

