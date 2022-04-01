
aux_source_directory(. BASE)

add_library(base ${BASE})
target_link_libraries(base pthread rt)

