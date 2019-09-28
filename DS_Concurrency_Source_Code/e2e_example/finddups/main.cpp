#include "dup_search.h"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Expected single command line argument: path" << std::endl;
    }

    dup_search dups(argv[1]);

    dups.begin();

    dups.get([](const duplicate* const dup)
    {
        std::cout << "Duplicates - Hash " << dup->hash << std::endl;
        for (auto file : dup->duplicates)
        {
            std::cout << "    " << file << std::endl;
        }
    });
}

