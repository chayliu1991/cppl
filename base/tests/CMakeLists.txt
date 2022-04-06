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

