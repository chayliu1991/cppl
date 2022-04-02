
aux_source_directory(. BASE)

add_library(cppl_base ${BASE})
target_link_libraries(cppl_base pthread rt)


if(BUILD_TESTS)
  add_subdirectory(tests)
endif()