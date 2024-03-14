#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include "HashFunctions.h"
#include "HashTables.h"
#include "Utils.h"
#include "defines.h"

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
    size_t memory_usage = getCurrentMemoryUsageInBytes();

    {
        Map map;
        init_func(map);

        const auto * end = data + size;
        for (const auto * current = data; current < end; ++current)
            ++map[*current];

        memory_usage = std::max(getCurrentMemoryUsageInBytes() - memory_usage, getPageSizeInBytes());
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

template <typename Key, typename Map, typename InitFunc = VoidInitialization<Map>>
void NOINLINE testopt(const Key * data, size_t size, std::string_view hash_table, std::string_view hash_function, InitFunc init_func = {})
{
    auto start = std::chrono::steady_clock::now();
    size_t map_size = 0;
    size_t memory_usage = getCurrentMemoryUsageInBytes();
    static constexpr size_t PREFETCH = 16;
    static constexpr size_t BLOCK = 512;
    std::vector<size_t> hash_values(BLOCK);

    {
        Map map;
        init_func(map);
        // const auto * end = data + size;
        size_t i = 0;
        for (; (i + BLOCK) < size; i += BLOCK)
        {
            for (size_t j = 0; j < BLOCK; j++) {
                size_t hashval = map.hash_function()(data[i + j]);
                hash_values[j] = hashval;
            }

            for (size_t j = 0, k = PREFETCH; j < BLOCK; j++, k++) {
                if (k < BLOCK) {
                    map.prefetch_hash(hash_values[k]);
                }
                map.lazy_emplace_with_hash(data[i + j], hash_values[j], [&](const auto& ctor) {
                    ctor(data[i + j], 1);
                });
            }
        }

        if (i <  size)
        {
            for (size_t j = 0; j < (size - i); j++) {
                size_t hashval = map.hash_function()(data[i + j]);
                hash_values[j] = hashval;
            }

            for (size_t j = 0, k = PREFETCH; j < (size - i); j++, k++) {
                if (k < (size - i)) {
                    map.prefetch_hash(hash_values[k]);
                }
                map.lazy_emplace_with_hash(data[i + j], hash_values[j], [&](const auto& ctor) {
                    ctor(data[i + j], 1);
                });
                // ++map[data[i + j]];
                // map.emplace_with_hash(hash_values[j], data[i + j]);
            }
        }

        memory_usage = std::max(getCurrentMemoryUsageInBytes() - memory_usage, getPageSizeInBytes());
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

                    if constexpr (HashTableType::has_initialization)
                        test<Key, HashTable>(
                            data, size, hash_table_type.description, hash_function_type.description, HashTableType::initialize);
                    else if constexpr (HashTableType::phmap_opt)
                        testopt<Key, HashTable>(
                            data, size, hash_table_type.description, hash_function_type.description);
                    else
                        test<Key, HashTable>(data, size, hash_table_type.description, hash_function_type.description);
                });
        });
}

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
