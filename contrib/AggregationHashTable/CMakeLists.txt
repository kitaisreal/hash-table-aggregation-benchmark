set (HEADERS
    GroupHashTable.h)

add_library(group_hash_table INTERFACE ${HEADERS})
target_include_directories(group_hash_table INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
