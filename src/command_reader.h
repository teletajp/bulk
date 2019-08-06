#pragma once
#include <memory>
#include "ireader.h"

namespace bulk
{
class CommandReader
{
    ReaderSubscriberPtr<std::string> box_;
public:
    CommandReader(uint32_t bulk_size);
    ~CommandReader();
    bool Read();
    void setSubscriber(ReaderSubscriberPtr<std::string>&& subscriber)
    {
        box_ = std::move(subscriber);
    }
};

}