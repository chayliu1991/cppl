cmake_minimum_required(VERSION 3.6)

project(cppl LANGUAGES C CXX VERSION 1.0.0)


if(CMAKE_PROJECT_NAME STREQUAL "cppl")
  option(BUILD_TESTS "Build Cppl Tests" ON)
endif()


set(CMAKE_CXX_FLAGS  "-DCHECK_PTHREAD_RETURN_VALUE -D_FILE_OFFSET_BITS=64 -Wall -Wextra -Werror -march=native -std=c++11 -rdynamic")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


set(3rdIncDir ${CMAKE_CURRENT_SOURCE_DIR}/3rd/googletest/inc/
              ${CMAKE_CURRENT_SOURCE_DIR}/3rd/zlib/inc/)
set(3rdLibDir ${CMAKE_CURRENT_SOURCE_DIR}/3rd/googletest/lib/
              ${CMAKE_CURRENT_SOURCE_DIR}/3rd/zlib/lib/)
set(3rdLibs libgtest_main.a libgtest.a libz.a)

set(BoostIncDir ${CMAKE_CURRENT_SOURCE_DIR}/3rd/boost/inc/)
set(BoostLibDir ${CMAKE_CURRENT_SOURCE_DIR}/3rd/boost/lib/)
set(BoostLibs libboost_atomic.a libboost_chrono.a libboost_container.a libboost_context.a libboost_contract.a
    libboost_coroutine.a libboost_date_time.a libboost_exception.a libboost_filesystem.a libboost_graph.a
    libboost_iostreams.a libboost_locale.a libboost_log.a libboost_log_setup.a libboost_prg_exec_monitor.a
    libboost_program_options.a libboost_random.a libboost_regex.a libboost_serialization.a
    libboost_system.a libboost_test_exec_monitor.a libboost_thread.a libboost_timer.a libboost_type_erasure.a
    libboost_unit_test_framework.a libboost_wave.a libboost_wserialization.a)



include_directories(${3rdIncDir} ${BoostIncDir})
link_directories(${3rdLibDir} ${BoostLibDir})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)

add_subdirectory(base)
add_subdirectory(net)
