aux_source_directory(. BaseSrc)

add_library(cppl_base ${BaseSrc})
target_link_libraries(cppl_base pthread rt)

if(BUILD_TESTS)
  add_subdirectory(tests)
endif()