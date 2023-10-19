#pragma once

#include <string>
#include <vector>
#include "defines.h"

size_t getPageSizeInBytes();

size_t getCurrentMemoryUsageInBytes();

struct Column
{
    std::string type;
    std::vector<char> data;
};

Column readColumnFromFile(std::string_view file_name);
