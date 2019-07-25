#include <iostream>
#include "console_printer.h"
#include <string>
namespace bulk
{

ConsolePrinter::ConsolePrinter()
{
}

ConsolePrinter::~ConsolePrinter()
{
}
void ConsolePrinter::Print(const std::string & data)
{
    std::cout << data;
}
}