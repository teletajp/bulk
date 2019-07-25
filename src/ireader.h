#pragma once
namespace bulk
{
template<class T>
class IReader
{
public:
    virtual bool OnRead(const T& data) = 0;
    virtual bool OnRead(T&& data) = 0;
    virtual ~IReader() = default;
};
}