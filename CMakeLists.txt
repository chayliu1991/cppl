cmake_minimum_required(VERSION 3.6)

project(muduo LANGUAGES C CXX VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "-DCHECK_PTHREAD_RETURN_VALUE -D_FILE_OFFSET_BITS=64 -Wall -Wextra -Werror -march=native -std=c++11 -rdynamic")



set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


add_subdirectory(base)
# add_subdirectory(net)
