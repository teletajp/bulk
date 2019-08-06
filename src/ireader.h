#pragma once
#include <memory>
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
template<class T>
using ReaderSubscriberPtr = std::unique_ptr<IReader<T>>;
}