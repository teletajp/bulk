#pragma once
#include <string>
#include <list>
#include <ctime>
#include "ibox.h"

namespace bulk
{
class CommandBox : public IBox<std::string>
{
public:
    enum class State
    {
        wait_limit,
        wait_brace
    };
private:
    time_t start_block_time_;
    std::list<std::string> commands_;
    State state_;
    uint32_t brace_nesting_;
    void Print(const std::string &data);
public:
    CommandBox(uint32_t max_command);
    ~CommandBox();
    bool OnRead(const std::string& el) override;
    bool OnRead(std::string&& el) override;
    bool Proccess() override;

};


}