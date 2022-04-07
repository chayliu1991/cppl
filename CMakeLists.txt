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

include_directories(${3rdIncDir})
link_directories(${3rdLibDir})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)

add_subdirectory(base)
#add_subdirectory(net)
