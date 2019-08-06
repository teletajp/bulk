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
    Proccess();
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
    if (!commands_.empty())
    {
        if (state_ == State::wait_brace && brace_nesting_ != 0)
            return false;
        for(auto &pr: printers_)
            pr->Print(start_block_time_, *this);
        
        Clear();
    }
    return true;
}
void CommandBox::Clear()
{
    commands_.clear();
    state_ = State::wait_limit;
    count_ = 0;
    brace_nesting_ = 0;
}
}