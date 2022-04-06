add_executable(atomic_test Atomic_test.cpp)
target_link_libraries(atomic_test cppl_base ${3rdLibs})

add_executable(mutex_test Mutex_test.cpp)
target_link_libraries(mutex_test cppl_base)

add_executable(process_info_test ProcessInfo_test.cpp)
target_link_libraries(process_info_test cppl_base)

add_executable(date_test Date_test.cpp)
target_link_libraries(date_test cppl_base ${3rdLibs})

add_executable(fileutil_test FileUtil_test.cpp)
target_link_libraries(fileutil_test cppl_base)

add_executable(logfile_test LogFile_test.cpp)
target_link_libraries(logfile_test cppl_base)

add_executable(logging_test Logging_test.cpp)
target_link_libraries(logging_test cppl_base)

add_executable(logstream_test LogStream_test.cpp)
target_link_libraries(logstream_test cppl_base ${3rdLibs})

add_executable(logstream_bench LogStream_bench.cpp)
target_link_libraries(logstream_bench cppl_base)

add_executable(async_logging_test AsyncLogging_test.cpp)
target_link_libraries(async_logging_test cppl_base)

add_executable(fork_test Fork_test.cpp)
target_link_libraries(fork_test cppl_base)

add_executable(exception_test Exception_test.cpp)
target_link_libraries(exception_test cppl_base)

add_executable(timestamp_test Timestamp_test.cpp)
target_link_libraries(timestamp_test cppl_base)

add_executable(timezone_test TimeZone_test.cpp)
target_link_libraries(timezone_test cppl_base)

add_executable(singleton_test Singleton_test.cpp)
target_link_libraries(singleton_test cppl_base)

add_executable(thread_test Thread_test.cpp)
target_link_libraries(thread_test cppl_base)

add_executable(thread_local_test ThreadLocal_test.cpp)
target_link_libraries(thread_local_test cppl_base)

add_executable(thread_local_singleton_test ThreadLocalSingleton_test.cpp)
target_link_libraries(thread_local_singleton_test cppl_base)

add_executable(thread_pool_test ThreadPool_test.cpp)
target_link_libraries(thread_pool_test cppl_base)

add_executable(blocking_queue_test BlockingQueue_test.cpp)
target_link_libraries(blocking_queue_test cppl_base)

add_executable(blocking_queue_bench BlockingQueue_bench.cpp)
target_link_libraries(blocking_queue_bench cppl_base)

add_executable(bounded_blocking_queue_test BoundedBlockingQueue_test.cpp)
target_link_libraries(bounded_blocking_queue_test cppl_base)


