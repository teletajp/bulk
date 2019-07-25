#include <iostream>
#include <string>
#include "version.h"
#include "command_reader.h"

void test()
{
   
}

int main(int argc, char const *argv[])
{
    //test();
    if (argc < 2)
        return -1;
    uint32_t bulk_size = 0;
    try
    {
        bulk_size = std::stoul(argv[1]);
    }
    catch (...)
    {
        return -2;
    }
    
    bulk::CommandReader reader(bulk_size);
    while (reader.Read());
    return 0;
}
