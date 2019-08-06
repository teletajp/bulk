#pragma once
#include <iostream>
#include "iprinter.h"

namespace bulk
{
template<typename T>
class ConsolePrinter: public IPrinter<T>
{
public:
    ConsolePrinter(){};
    ~ConsolePrinter(){};
    void Print(std::time_t wt, const T& data) override
    {
        std::cout << data;
    }

};

}