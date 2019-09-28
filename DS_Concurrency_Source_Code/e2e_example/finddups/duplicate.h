#pragma once

#include <string>
#include <list>

class duplicate
{
public:
    std::string hash;
    std::list<std::string> duplicates;

    duplicate(std::string fileHash, std::string file)
        : hash(fileHash)
    {
        duplicates.push_back(file);
    }
};
