#include <iostream>
#include <memory>
#include "command_box.h"
#include "console_printer.h"
#include "file_printer.h"
namespace bulk
{
void CommandBox::Print(const std::string &data)
{
    
}

CommandBox::CommandBox(uint32_t max_command):IBox(max_command), state_(State::wait_limit), brace_nesting_(0)
{

}

CommandBox::~CommandBox()
{
}
bool CommandBox::OnRead(const std::string & el)
{
    if (el == "{")
    {
        state_ = State::wait_brace;
        brace_nesting_++;
    }
    else if (el == "}")
    {
        if (--brace_nesting_ == 0)
        {
            state_ = State::wait_limit;
            Proccess();
            commands_.clear();
        }
    }
    else
    {
        if (state_ == State::wait_brace)
        {
            commands_.push_back(el);
            ++count_;
            if (count_ == 1) time(&start_block_time_);
        }
        else if (state_ == State::wait_limit)
        {
            if (limit_ == 0) return false;
            commands_.push_back(el);
            ++count_;
            if (count_ == 1) time(&start_block_time_);
            if (count_ == limit_)
            {
                Proccess();
                commands_.clear();
            }
        }
        else
            return false;
    }
   
    return true;
}
bool CommandBox::OnRead(std::string && el)
{
    if (el == "{")
    {
        state_ = State::wait_brace;
        ++brace_nesting_;
    }
    else if (el == "}")
    {
        if (state_ != State::wait_brace) return false;
        if (--brace_nesting_ == 0)
        {
            state_ = State::wait_limit;
            Proccess();
            commands_.clear();
        }
    }
    else
    {
        if (state_ == State::wait_brace)
        {
            commands_.emplace_back(std::move(el));
            ++count_;
            if (count_ == 1) time(&start_block_time_);
        }
        else if (state_ == State::wait_limit)
        {
            if (limit_ == 0) return false;
            commands_.emplace_back(std::move(el));
            ++count_;
            if (count_ == 1) time(&start_block_time_);
            if (count_ == limit_)
            {
                Proccess();
                commands_.clear();
            }
        }
        else
            return false;
    }

    return true;
}
bool CommandBox::Proccess()
{
    std::unique_ptr<IPrinter<std::string>> console = std::make_unique<ConsolePrinter>();
    std::unique_ptr<IPrinter<std::string>> file = std::make_unique<FilePrinter>("bulk" + std::to_string(start_block_time_) + ".log");
    std::string data = "bulk: ";
    for (const auto& el : commands_)
    {
        data += el;
        if (count_ != 1)
            data += ",";
        else
            data += "\n";
        --count_;
    }
    console->Print(data);
    file->Print(data);
    return true;
}
}