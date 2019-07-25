#pragma once
#include "iprinter.h"

namespace bulk
{
class ConsolePrinter: public IPrinter<std::string>
{
public:
    ConsolePrinter();
    ~ConsolePrinter();
    void Print(const std::string& data) override;

};

}