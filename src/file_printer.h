#pragma once
#include <string>
#include <fstream>
#include "iprinter.h"
namespace bulk
{
class FilePrinter: public IPrinter<std::string>
{
    std::ofstream file_stream_;
    std::string file_name_;
public:
    FilePrinter(std::string file_name);
    ~FilePrinter();
    void Print(const std::string &data) override;
};
}