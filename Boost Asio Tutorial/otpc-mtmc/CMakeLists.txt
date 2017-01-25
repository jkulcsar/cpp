PROJECT(test-asio)

cmake_minimum_required(VERSION 2.8)

find_package(Boost)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "Could not find boost")
endif (NOT Boost_FOUND)


include_directories(${Boost_INCLUDE_DIRS}
        ./threadpool/)
link_directories(${Boost_LIBRARY_DIRS})

#if(DEBUG_BUILD)
#  set(BOOST_LIB_SUFFIX "-d")
#endif(DEBUG_BUILD)

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(BOOST_LIB_SUFFIX -mt)
SET(USED_LIBS boost_system${BOOST_LIB_SUFFIX} boost_thread${BOOST_LIB_SUFFIX} boost_regex${BOOST_LIB_SUFFIX})

#INCLUDE_DIRECTORIES(~/exp/include)
#LINK_DIRECTORIES(~/exp/lib)

ADD_DEFINITIONS(-g -Wall -ansi)

ADD_EXECUTABLE(test-otpc test-otpc.cpp test-otpc-conn.cpp)
TARGET_LINK_LIBRARIES(test-otpc ${USED_LIBS})

ADD_EXECUTABLE(test-otpc-tp test-otpc-tp.cpp test-otpc-conn.cpp)
TARGET_LINK_LIBRARIES(test-otpc-tp ${USED_LIBS})

ADD_EXECUTABLE(test-mcmt test-mcmt.cpp)
TARGET_LINK_LIBRARIES(test-mcmt ${USED_LIBS})

#ADD_EXECUTABLE(test-pipelined test-pipelined.cpp)
#TARGET_LINK_LIBRARIES(test-pipelined ${USED_LIBS})

#ADD_EXECUTABLE(proxy proxy.cpp proxy-server.cpp proxy-conn.cpp)
#TARGET_LINK_LIBRARIES(proxy ${USED_LIBS})
