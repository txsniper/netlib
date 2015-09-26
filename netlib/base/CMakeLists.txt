set(base_SRCS
    Condition.cc
    ThreadInfo.cc
    Thread.cc
    ThreadPool.cc
    CountDownLatch.cc
    )
#add_library(netlib_base ${base_SRCS})
#target_link_libraries(netlib_base pthread rt)

add_library(netlib_base_cpp11 ${base_SRCS})
target_link_libraries(netlib_base_cpp11 pthread rt)
set_target_properties(netlib_base_cpp11 PROPERTIES COMPILE_FLAGS "-std=c++0x")

#install(TARGETS netlib_base DESTINATION lib)
install(TARGETS netlib_base_cpp11 DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/netlib/base)

add_subdirectory(tests)
