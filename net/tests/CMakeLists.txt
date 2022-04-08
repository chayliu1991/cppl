set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/net/)

add_executable(buffer_test Buffer_test.cpp)
target_link_libraries(buffer_test cppl_base cppl_net ${3rdLibs})




