#pragma once

#include <string>
#include <unordered_map>

#include <AggregationHashTable/GroupHashTable.h>
#include <ClickHouseHashTable/HashMap.h>
#include <absl/container/flat_hash_map.h>
#include <hopscotch-map/include/tsl/hopscotch_map.h>
#include <unordered_dense/include/ankerl/unordered_dense.h>
#include <flat_hash_map/bytell_hash_map.hpp>
#include <flat_hash_map/flat_hash_map.hpp>

#include "defines.h"

template <typename Key, typename Hash>
struct ClickHouseHashTableType
{
    using HashTable = HashMap<Key, UInt64, Hash>;
    static constexpr std::string_view description = "ClickHouse HashMap";
};

template <typename Key, typename Hash>
struct AbseilHashTableType
{
    using HashTable = ::absl::flat_hash_map<Key, UInt64, Hash>;
    static constexpr std::string_view description = "absl::flat_hash_map";
};

template <typename Key, typename Hash>
struct TslHopscotchHashTableType
{
    using HashTable = tsl::hopscotch_map<Key, UInt64, Hash>;
    static constexpr std::string_view description = "tsl::hopscotch_map";
};

template <typename Key, typename Hash>
struct AnkerlUnorderedDenseHashTableType
{
    using HashTable = ankerl::unordered_dense::map<Key, UInt64, Hash>;
    static constexpr std::string_view description = "ankerl::unordered_dense::map";
};

template <typename Key, typename Hash>
struct SkaFlatHashTableType
{
    using HashTable = ska::flat_hash_map<Key, UInt64, Hash>;
    static constexpr std::string_view description = "ska::flat_hash_map";
};

template <typename Key, typename Hash>
struct SkaBytellHashTableType
{
    using HashTable = ska::bytell_hash_map<Key, UInt64, Hash>;
    static constexpr std::string_view description = "ska::bytell_hash_map";
};

template <typename Key, typename Hash>
struct StandardHashTableType
{
    using HashTable = std::unordered_map<Key, UInt64, Hash>;
    static constexpr std::string_view description = "std::unordered_map";
};

template <typename Key, typename Hash, typename Callback>
void dispatchHashTableType(std::string_view hash_table_type, Callback && callback)
{
    if (hash_table_type == "ch_hash_map")
        callback(ClickHouseHashTableType<Key, Hash>());
    else if (hash_table_type == "absl_hash_map")
        callback(AbseilHashTableType<Key, Hash>());
    else if (hash_table_type == "tsl_hopscotch_hash_map")
        callback(TslHopscotchHashTableType<Key, Hash>());
    else if (hash_table_type == "ankerl_unordered_dense_hash_map")
        callback(AnkerlUnorderedDenseHashTableType<Key, Hash>());
    else if (hash_table_type == "ska_flat_hash_map")
        callback(SkaFlatHashTableType<Key, Hash>());
    else if (hash_table_type == "ska_bytell_hash_map")
        callback(SkaBytellHashTableType<Key, Hash>());
    else if (hash_table_type == "std_hash_map")
        callback(StandardHashTableType<Key, Hash>());
    else
        throw std::runtime_error("Invalid hash table type " + std::string(hash_table_type));
}