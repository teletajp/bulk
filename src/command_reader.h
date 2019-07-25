#pragma once
#include <memory>
#include "ireader.h"

namespace bulk
{
class CommandReader
{
    std::unique_ptr<IReader<std::string>> box_;
public:
    CommandReader(uint32_t bulk_size);
    ~CommandReader();
    bool Read();
};

}