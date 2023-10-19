#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

#include "defines.h"
#include "Utils.h"
#include "HashFunctions.h"
#include "HashTables.h"

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

                    if constexpr (HashTableType::has_initialization)
                        test<Key, HashTable>(data, size, hash_table_type.description, hash_function_type.description, HashTableType::initialize);
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
