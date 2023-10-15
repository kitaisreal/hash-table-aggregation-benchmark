set (SOURCES
    Allocator.cpp)

set (HEADERS
    Hash.h
    Allocator.h
    HashTableAllocator.h
    HashTable.h
    HashMap.h)

add_library(clickhouse_hash_table STATIC)
target_sources(clickhouse_hash_table PRIVATE ${SOURCES} ${HEADERS})
target_include_directories(clickhouse_hash_table INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
