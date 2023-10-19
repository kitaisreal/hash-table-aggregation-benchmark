# Add ClickHouseHashTable library

add_subdirectory(ClickHouseHashTable EXCLUDE_FROM_ALL)

# Add Abseil swiss tables library

set(BUILD_TESTING OFF)
set(ABSL_PROPAGATE_CXX_STD ON)

add_subdirectory(abseil-cpp EXCLUDE_FROM_ALL)
add_library(abseil_swiss_tables INTERFACE)

target_link_libraries(abseil_swiss_tables INTERFACE
  absl::flat_hash_map
  absl::flat_hash_set
)

get_target_property(FLAT_HASH_MAP_INCLUDE_DIR absl::flat_hash_map INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(abseil_swiss_tables SYSTEM BEFORE INTERFACE ${FLAT_HASH_MAP_INCLUDE_DIR})

get_target_property(FLAT_HASH_SET_INCLUDE_DIR absl::flat_hash_set INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(abseil_swiss_tables SYSTEM BEFORE INTERFACE ${FLAT_HASH_SET_INCLUDE_DIR})

# Add hopscotch-map library
add_subdirectory(hopscotch-map EXCLUDE_FROM_ALL)

# Add unordered_dense library
add_subdirectory(unordered_dense EXCLUDE_FROM_ALL)

# Add flat_hash_map library

set(FLAT_HASH_MAP_HEADERS
  flat_hash_map/bytell_hash_map.hpp
  flat_hash_map/flat_hash_map.hpp
  flat_hash_map/unordered_map.hpp
  )

add_library(flat_hash_map INTERFACE ${FLAT_HASH_MAP_HEADERS})

# Add sparsehash library
add_library(sparsehash INTERFACE)
target_include_directories(sparsehash SYSTEM BEFORE INTERFACE "${PROJECT_SOURCE_DIR}/contrib/sparsehash-c11")
