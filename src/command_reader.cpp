#include <iostream>
#include "command_reader.h"
#include "command_box.h"
namespace bulk
{

CommandReader::CommandReader(uint32_t bulk_size): box_(std::make_unique<CommandBox>(bulk_size))
{
}

CommandReader::~CommandReader()
{
}
bool CommandReader::Read()
{
    std::string cmd;
    if (std::getline(std::cin, cmd))
    {
        box_->OnRead(std::move(cmd));
        return true;
    }
    return false;
}
}