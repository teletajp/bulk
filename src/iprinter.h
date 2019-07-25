#pragma once
namespace bulk
{
template<class T>
class IPrinter
{
public:
    virtual void Print(const T& data) = 0;
    virtual ~IPrinter() = default;
};

}