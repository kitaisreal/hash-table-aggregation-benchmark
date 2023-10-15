#pragma once

#include <string>
#include <functional>

#include <ClickHouseHashTable/Hash.h>
#include <absl/hash/hash.h>

template <typename Key>
struct StandardHashFunctionType
{
    using Hash = std::hash<Key>;
    static constexpr std::string_view description = "std::hash";
};

template <typename Key>
struct ClickHouseHashFunctionType
{
    using Hash = DefaultHash<Key>;
    static constexpr std::string_view description = "ClickHouse hash";
};

template <typename Key>
struct AbslHashFunctionType
{
    using Hash = absl::Hash<Key>;
    static constexpr std::string_view description = "absl::Hash";
};

template <typename Key, typename Callback>
void dispatchHashFunctionType(std::string_view hash_function_type, Callback && callback)
{
    if (hash_function_type == "std_hash")
        callback(StandardHashFunctionType<Key>());
    else if (hash_function_type == "ch_hash")
        callback(ClickHouseHashFunctionType<Key>());
    else if (hash_function_type == "absl_hash")
        callback(AbslHashFunctionType<Key>());
    else
        throw std::runtime_error("Invalid hash function type " + std::string(hash_function_type));
}
