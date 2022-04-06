add_executable(atomic_test Atomic_test.cpp)

add_executable(date_test Date_test.cpp)
target_link_libraries(date_test cppl_base)

add_executable(fileutil_test FileUtil_test.cpp)
target_link_libraries(fileutil_test cppl_base)

add_executable(logfile_test LogFile_test.cpp)
target_link_libraries(logfile_test cppl_base)
