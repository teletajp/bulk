#pragma once
#include <cstdint>
#include "ireader.h"
#include "iprinter.h"
namespace bulk
{
template<class T>
class IBox : public IReader<T>
{
protected:
    const uint32_t limit_;
    uint32_t count_;
public:
    IBox(uint32_t limit) :limit_(limit), count_(0) {}
    virtual bool OnRead(const T& el) = 0;
    virtual bool OnRead(T&& el) = 0;
    virtual bool Proccess() = 0;
    virtual ~IBox() = default;
};
}