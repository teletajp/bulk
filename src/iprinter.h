#pragma once
#include <ctime>
#include <memory>
namespace bulk
{
template<class T>
class IPrinter
{
public:
    virtual void Print(std::time_t wt, const T& data) = 0;
    virtual ~IPrinter() = default;
};
template<class T>
using PrinterPtr = std::unique_ptr<IPrinter<T>>;

}