#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <fstream>
#include <filesystem>

#include <unordered_map>

// #include <sparsehash/dense_hash_map>
// #include <sparsehash/sparse_hash_map>
// #include <absl/container/flat_hash_map.h>

#define NOINLINE __attribute__((noinline))

using UInt8 = uint8_t;
using UInt16 = uint16_t;
using UInt32 = uint32_t;
using UInt64 = uint64_t;

using Int8 = int8_t;
using Int16 = int16_t;
using Int32 = int32_t;
using Int64 = int64_t;

template <typename Key>
using DefaultHash = std::hash<Key>;

template <typename Map>
struct VoidInitialization
{
    void operator()(const Map & map)
    {}
};

template <typename Key, typename Map, typename InitFunc = VoidInitialization<Map>>
void NOINLINE test(const Key * data, size_t size, std::string_view hash_table_name, InitFunc init_func = {})
{
    auto start = std::chrono::steady_clock::now();

    Map map;
    init_func(map);

    for (const auto * end = data + size; data < end; ++data)
        ++map[*data];

    auto finish = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start);
    double elapsed_seconds = static_cast<double>(duration.count()) / 1000000000ULL;

    std::cout << hash_table_name
        << ":\nElapsed: " << elapsed_seconds
        << " (" << size / elapsed_seconds << " elem/sec.)"
        << ", map size: " << map.size() << "\n";
}

template <typename Key>
static void NOINLINE testForHashMapType(const Key * data, size_t size, std::string_view method)
{
    // if (method == "ch_hash_map")
    // {
    //     test<Key, HashMap<Key, UInt64, DefaultHash<Key>>>(data.data(), data.size(), "CH HashMap");
    // }
    // else if (method == 1)
    // {
    //     test<Key, ::google::dense_hash_map<Key, UInt64, absl::Hash<Key>>>(data.data(), data.size(), "Google DenseMap", [](auto & map){ map.set_empty_key(0); });
    // }
    // else if (method == 2)
    // {
    //     test<Key, ::absl::flat_hash_map<Key, UInt64>>(data.data(), data.size(), "Abseil HashMap");
    // }
    // else if (method == 3)
    // {
    //     test<Key, ::absl::flat_hash_map<Key, UInt64, DefaultHash<Key>>>(data.data(), data.size(), "Abseil HashMap with CH Hash");
    // }
    // else
    if (method == "std_hash_map_std_hash")
    {
        test<Key, std::unordered_map<Key, UInt64>>(data, size, "std::unordered_map");
    }
    else if (method == "std_hash_map_ch_hash")
    {
        test<Key, std::unordered_map<Key, UInt64>>(data, size, "std::unordered_map");
    }
    else if (method == "std_hash_map_absl_hash")
    {
        test<Key, std::unordered_map<Key, UInt64>>(data, size, "std::unordered_map");
    }
    else
    {
        throw std::runtime_error("Unexpected hash map method passed");
    }
}

template <typename T>
std::vector<T> ReadData(std::string_view file_name)
{
    auto file_size = std::filesystem::file_size(file_name);
    if (file_size % sizeof(T) != 0)
        throw std::runtime_error("Invalid binary file. Binary size be multiplication of type size " + std::to_string(sizeof(T)));

    std::vector<T> data(file_size / sizeof(T));

    std::ifstream stream(std::string(file_name), std::ios_base::binary);
    stream.read(reinterpret_cast<char *>(data.data()), data.size() * sizeof(T));

    return data;
}

template <typename Key>
static void NOINLINE testForKeyType(std::string_view method, std::string_view type_name, std::string_view file_name)
{
    auto data = ReadData<Key>(file_name);

    std::cout << "Method " << method << " typename " << type_name << " file name " << file_name << " elements size " << data.size() << '\n';
    testForHashMapType(data.data(), data.size(), method);
}

// https://github.com/martinus/unordered_dense
// https://github.com/Tessil/robin-map
// https://github.com/Tessil/hopscotch-map
// https://github.com/facebook/folly


int main(int argc, char ** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: hash_tables_aggregation_benchmark strategy type_name file_name\n";
        return 1;
    }

    std::string method = argv[1];
    std::string type_name = argv[2];
    std::string file_name = argv[3];

    try
    {
        if (type_name == "UInt8")
            testForKeyType<UInt8>(method, "UInt8", file_name);
        else if (type_name == "UInt16")
            testForKeyType<UInt16>(method, "UInt16", file_name);
        else if (type_name == "UInt32")
            testForKeyType<UInt32>(method, "UInt32", file_name);
        else if (type_name == "UInt64")
            testForKeyType<UInt64>(method, "UInt64", file_name);
        else if (type_name == "Int8")
            testForKeyType<Int8>(method, "Int8", file_name);
        else if (type_name == "Int16")
            testForKeyType<Int16>(method, "Int16", file_name);
        else if (type_name == "Int32")
            testForKeyType<Int32>(method, "Int32", file_name);
        else if (type_name == "Int64")
            testForKeyType<Int64>(method, "Int64", file_name);
        else
            throw std::runtime_error("Unexpected column type passed");
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what() << '\n';
        return 1;
    }

    return 0;
}
