#include "utils.h"

#include <iomanip>
#include <vector>
#include <chrono>
#include <fstream>

#include <unistd.h>

namespace
{

size_t readVarUInt(UInt64 & x, std::istream & istr)
{
    x = 0;

    size_t read_size = 0;
    for (size_t i = 0; i < 9; ++i)
    {
        UInt64 byte = istr.get();
        ++read_size;

        x |= (byte & 0x7F) << (7 * i);

        if (!(byte & 0x80))
            break;
    }

    return read_size;
}

}

size_t getCurrentMemoryUsageInBytes()
{
    std::ifstream stream("/proc/self/statm", std::ios_base::in);

    if (!stream.is_open())
        return 0;

    int64_t ignore = 0;
    int64_t rss = 0;

    stream >> ignore;
    stream >> rss;

    Int64 page_size = sysconf(_SC_PAGESIZE);
    if (page_size < 0)
        return 0;

    return rss * page_size;
}

Column readColumnFromFile(std::string_view file_name)
{
    auto file_size = std::filesystem::file_size(file_name);
    std::ifstream stream(std::string(file_name), std::ios_base::binary);

    size_t read_bytes_size = 0;

    UInt64 number_of_columns = 0;
    read_bytes_size += readVarUInt(number_of_columns, stream);
    if (number_of_columns != 1)
        throw std::runtime_error("Invalid number of columns. Expected 1 column.");

    UInt64 column_name_length = 0;
    read_bytes_size += readVarUInt(column_name_length, stream);

    std::string column_name(column_name_length, ' ');
    stream.read(column_name.data(), column_name_length);
    read_bytes_size += column_name_length;

    UInt64 type_name_length = 0;
    read_bytes_size += readVarUInt(type_name_length, stream);

    std::string type_name(type_name_length, ' ');
    stream.read(type_name.data(), type_name_length);
    read_bytes_size += type_name_length;

    size_t column_data_size = file_size - read_bytes_size;

    std::vector<char> data(column_data_size);
    stream.read(data.data(), column_data_size);

    return Column{std::move(type_name), std::move(data)};
}
