include(CheckSymbolExists)


aux_source_directory(. NetSrc)


check_symbol_exists(accept4 "sys/socket.h" HAVE_ACCEPT4)


if(NOT HAVE_ACCEPT4)
  set_source_files_properties(SocketsOps.cc PROPERTIES COMPILE_FLAGS "-DNO_ACCEPT4")
endif()


add_library(cppl_net ${NetSrc})
target_link_libraries(cppl_net cppl_base)

# if(BUILD_TESTS)
#   add_subdirectory(tests)
# endif()