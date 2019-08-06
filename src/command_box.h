#pragma once
#include <string>
#include <list>
#include <ctime>
#include "ibox.h"
#include "iprinter.h"
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
    std::list<PrinterPtr<CommandBox>> printers_;
    State state_;
    uint32_t brace_nesting_;
    void Print(const std::string &data);
    void Clear();
public:
    CommandBox(uint32_t max_command);
    ~CommandBox();
    bool OnRead(const std::string& el) override;
    bool OnRead(std::string&& el) override;
    bool Proccess() override;
    void addPrinter(PrinterPtr<CommandBox>&& printer)
    {
        printers_.emplace_back(std::move(printer));
    }
    friend std::ostream &operator<<( std::ostream &output, const CommandBox &box )
    { 
        auto count = box.count_;
        output << "bulk:";
        for (const auto& el : box.commands_)
        {
            output << el;
            if (count != 1)
                output << ",";
            else
                output << "\n";
            --count;
        }
         return output;            
    }
};


}