#include "file_printer.h"
namespace bulk
{

FilePrinter::FilePrinter(std::string file_name):file_name_(file_name)
{
}

FilePrinter::~FilePrinter()
{
    if (file_stream_.is_open())
    {
        file_stream_.close();
    }
}

void FilePrinter::Print(const std::string& data)
{
    if (!file_stream_.is_open())
        file_stream_.open(file_name_);

    if (file_stream_.is_open())
    {
        file_stream_ << data;
    }
}

}