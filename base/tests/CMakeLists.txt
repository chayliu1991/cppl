add_executable(atomic_test Atomic_test.cpp)
target_link_libraries(atomic_test cppl_base ${3rdLibs})


add_executable(date_test Date_test.cpp)
target_link_libraries(date_test cppl_base ${3rdLibs})

add_executable(fileutil_test FileUtil_test.cpp)
target_link_libraries(fileutil_test cppl_base)

add_executable(logfile_test LogFile_test.cpp)
target_link_libraries(logfile_test cppl_base)

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

