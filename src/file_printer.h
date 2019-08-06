#pragma once
#include <fstream>
#include <string>
#include "iprinter.h"
namespace bulk
{
template<typename T>
class FilePrinter: public IPrinter<T>
{
    std::ofstream file_stream_;
    std::string file_name_;
public:
    FilePrinter(std::string file_name):file_name_(file_name){}
    ~FilePrinter()
    {
        if (file_stream_.is_open())
            file_stream_.close();
    }
    void Print(std::time_t wt, const T& data) override
    {
        if (!file_stream_.is_open())
            file_stream_.open(file_name_ + std::to_string(wt) + ".log", std::ios_base::app);

        if (file_stream_.is_open())
        {
            file_stream_ << data;
            file_stream_.close();
        }
    }
};

}