add_executable(threadTest threadTest.cc)
target_link_libraries(threadTest netlib_base_cpp11)
add_executable(blockingQueueTest BlockingQueueTest.cc)
target_link_libraries(blockingQueueTest netlib_base_cpp11)
add_executable(threadPoolTest ThreadPoolTest.cc)
target_link_libraries(threadPoolTest netlib_base_cpp11)
