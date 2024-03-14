include_directories("${PROJECT_SOURCE_DIR}/contrib/parallel-hashmap/")

add_headers_and_sources(hash_table_aggregation_benchmark ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(hash_table_aggregation_benchmark ${hash_table_aggregation_benchmark_headers} ${hash_table_aggregation_benchmark_sources})
target_link_libraries(hash_table_aggregation_benchmark PRIVATE
    clickhouse_hash_table
    abseil_swiss_tables
    hopscotch_map
    unordered_dense
    flat_hash_map
    sparsehash)
