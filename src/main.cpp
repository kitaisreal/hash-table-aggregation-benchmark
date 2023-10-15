#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include "defines.h"
#include "hash_functions.h"
#include "hash_tables.h"
#include "utils.h"

template <typename Map>
struct VoidInitialization
{
    void operator()(const Map & map) { (void)(map); }
};

template <typename Key, typename Map, typename InitFunc = VoidInitialization<Map>>
void NOINLINE test(const Key * data, size_t size, std::string_view hash_table, std::string_view hash_function, InitFunc init_func = {})
{
    auto start = std::chrono::steady_clock::now();
    size_t map_size = 0;
    size_t memory_usage = 0;

    {
        Map map;
        init_func(map);

        for (const auto * end = data + size; data < end; ++data)
            ++map[*data];

        memory_usage = getCurrentMemoryUsageInBytes() - (sizeof(Key) * size);
        map_size = map.size();
    }

    auto finish = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);
    double elapsed_seconds = static_cast<double>(duration.count()) / 1000000000ULL;

    std::cout << "Hash table: " << hash_table << '\n';
    std::cout << "Hash function: " << hash_function << '\n';
    std::cout << "Hash table size: " << map_size << '\n';

    std::cout << "Elapsed: " << elapsed_seconds << " (" << static_cast<size_t>(size / elapsed_seconds) << " elem/sec.) " << '\n';
    std::cout << "Memory usage: " << memory_usage << "\n";
}

template <typename Key>
static void NOINLINE
testForHashMapType(std::string_view hash_table_type, std::string_view hash_function_type, const Key * data, size_t size)
{
    dispatchHashFunctionType<Key>(
        hash_function_type,
        [&](auto && hash_function_type)
        {
            using HashFunctionType = std::decay_t<decltype(hash_function_type)>;
            using Hash = typename HashFunctionType::Hash;

            dispatchHashTableType<Key, Hash>(
                hash_table_type,
                [&](auto && hash_table_type)
                {
                    using HashTableType = std::decay_t<decltype(hash_table_type)>;
                    using HashTable = typename HashTableType::HashTable;
                    test<Key, HashTable>(data, size, hash_table_type.description, hash_function_type.description);
                });
        });
}

// template <typename Key>
// static void NOINLINE testForHashMapType(const Key * data, size_t size, std::string_view method)
// {
//     if (method == "ch_hash_map_std_hash")
//         test<Key, HashMap<Key, UInt64, StdHash<Key>>>(data, size, "ClickHouse HashMap Standard Hash");
//     else if (method == "ch_hash_map_ch_hash")
//         test<Key, HashMap<Key, UInt64, DefaultHash<Key>>>(data, size, "ClickHouse HashMap ClickHouse Hash");
//     else if (method == "ch_hash_map_absl_hash")
//         test<Key, HashMap<Key, UInt64, absl::Hash<Key>>>(data, size, "ClickHouse HashMap Abseil Hash");
//     else if (method == "abseil_flat_hash_map_std_hash")
//         test<Key, ::absl::flat_hash_map<Key, UInt64, StdHash<Key>>>(data, size, "Abseil HashMap Standard Hash");
//     else if (method == "abseil_flat_hash_map_ch_hash")
//         test<Key, ::absl::flat_hash_map<Key, UInt64, DefaultHash<Key>>>(data, size, "Abseil HashMap ClickHouse Hash");
//     else if (method == "abseil_flat_hash_map_absl_hash")
//         test<Key, ::absl::flat_hash_map<Key, UInt64, absl::Hash<Key>>>(data, size, "Abseil HashMap Abseil Hash");
// else if (method == "hopscotch_hash_map_std_hash")
//     test<Key, tsl::hopscotch_map<Key, UInt64, StdHash<Key>>>(data, size, "Tsl Hopscotch HashMap Standard Hash");
//     else if (method == "hopscotch_hash_map_ch_hash")
//         test<Key, tsl::hopscotch_map<Key, UInt64, DefaultHash<Key>>>(data, size, "Tsl Hopscotch HashMap ClickHouse Hash");
//     else if (method == "hopscotch_hash_map_absl_hash")
//         test<Key, tsl::hopscotch_map<Key, UInt64, absl::Hash<Key>>>(data, size, "Tsl Hopscotch HashMap Abseil Hash");
// else if (method == "unordered_dence_std_hash")
//     test<Key, ankerl::unordered_dense::map<Key, UInt64, StdHash<Key>>>(data, size, "ankerl::unordered_dense::map Standard Hash");
// else if (method == "unordered_dence_ch_hash")
//     test<Key, ankerl::unordered_dense::map<Key, UInt64, DefaultHash<Key>>>(data, size, "ankerl::unordered_dense::map ClickHouse Hash");
// else if (method == "unordered_dence_absl_hash")
//     test<Key, ankerl::unordered_dense::map<Key, UInt64, absl::Hash<Key>>>(data, size, "ankerl::unordered_dense::map Abseil Hash");
// else if (method == "ska_flat_hash_map")
//     test<Key, ska::flat_hash_map<Key, UInt64>>(data, size, "ska::flat_hash_map");
// else if (method == "ska_bytell_hash_map")
//     test<Key, ska::bytell_hash_map<Key, UInt64>>(data, size, "ska::bytell_hash_map");
// else if (method == "std_hash_map_std_hash")
//         test<Key, std::unordered_map<Key, UInt64>>(data, size, "std::unordered_map");
//     else if (method == "std_hash_map_ch_hash")
//         test<Key, std::unordered_map<Key, UInt64>>(data, size, "std::unordered_map with ClickHouse hash");
//     else if (method == "std_hash_map_absl_hash")
//         test<Key, std::unordered_map<Key, UInt64>>(data, size, "std::unordered_map with Abseil hash");
//     else
//         throw std::runtime_error("Unexpected hash map method " + std::string(method) + " passed");
// }

// template <typename Key>
// static void NOINLINE testForHashMapType(const Key * data, size_t size, std::string_view hash_table, std::string_view hash)
// {
//     std::string hash_table_value = std::string(hash_table);
//     hash_table_value += hash;
//     testForHashMapType(data, size, hash_table_value);
// }


template <typename Key>
static void NOINLINE testForKeyType(
    std::string_view hash_table_type,
    std::string_view hash_function_type,
    std::string_view file_name,
    std::string_view key_type_name,
    const std::vector<char> & data)
{
    size_t size = data.size();
    if (size % sizeof(Key) != 0)
        throw std::runtime_error(
            "Invalid column data size. Column data size must be divisible by type size " + std::to_string(sizeof(Key)));

    size_t elements_size = size / sizeof(Key);
    auto * data_typed = reinterpret_cast<const Key *>(data.data());

    std::cout << "Hash table type: " << hash_table_type << '\n';
    std::cout << "Hash function type: " << hash_function_type << '\n';
    std::cout << "Key type name: " << key_type_name << '\n';
    std::cout << "File name: " << file_name << '\n';
    std::cout << "Keys size: " << elements_size << '\n';

    testForHashMapType(hash_table_type, hash_function_type, data_typed, elements_size);
}

static void runBenchmark(std::string_view hash_table_type, std::string_view hash_function_type, std::string_view file_name)
{
    auto column = readColumnFromFile(file_name);

    if (column.type == "UInt8")
        testForKeyType<UInt8>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "UInt16")
        testForKeyType<UInt16>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "UInt32")
        testForKeyType<UInt32>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "UInt64")
        testForKeyType<UInt64>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "Int8")
        testForKeyType<Int8>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "Int16")
        testForKeyType<Int16>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "Int32")
        testForKeyType<Int32>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else if (column.type == "Int64")
        testForKeyType<Int64>(hash_table_type, hash_function_type, file_name, column.type, column.data);
    else
        throw std::runtime_error("Unexpected column type " + column.type + " passed");
}

int main(int argc, char ** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: hash_table_aggregation_benchmark hash_table_type hash_function_type file_name\n";
        return 1;
    }

    std::string hash_table_type = argv[1];
    std::string hash_function_type = argv[2];
    std::string file_name = argv[3];

    try
    {
        runBenchmark(hash_table_type, hash_function_type, file_name);
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    return 0;
}
