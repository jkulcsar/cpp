
SET(SIMPLE_FILTER_LIBS boost_system${BOOST_LIB_SUFFIX} boost_iostreams${BOOST_LIBS_SUFFIX})

add_executable(simple_filter_usage simple_filter_usage.cpp)
target_link_libraries(simple_filter_usage ${SIMPLE_FILTER_LIBS})
