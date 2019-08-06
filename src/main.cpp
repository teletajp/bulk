#include <iostream>
#include <string>
#include "version.h"
#include "command_reader.h"
#include "command_box.h"
#include "console_printer.h"
#include "file_printer.h"
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
    
    std::unique_ptr<bulk::CommandBox> box = std::make_unique<bulk::CommandBox> (bulk_size);
    box->addPrinter(std::make_unique<bulk::ConsolePrinter<bulk::CommandBox>>());
    box->addPrinter(std::make_unique<bulk::FilePrinter<bulk::CommandBox>>("bulk"));
    bulk::CommandReader reader(bulk_size);
    reader.setSubscriber(std::move(box));
    while (reader.Read());
    return 0;
}
