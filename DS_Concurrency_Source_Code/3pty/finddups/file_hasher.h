#pragma once

#include "disk_reader.h"
#include <string>

class file_hasher
{
private:
    static disk_reader disk;

    file_hasher() { }

public:
    // returns the MD5 hash of the specified file's contents
    static std::string get_md5_hash(const std::string& file);
};