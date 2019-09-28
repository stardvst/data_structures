#include "file_hasher.h"
#include "md5.h"

#include <fstream>

// all disk reads go through this class
// it limits the number of concurrent readers
// to mitigate disk thrashing
disk_reader file_hasher::disk(1);

std::string file_hasher::get_md5_hash(const std::string& file)
{
    const int size = 4096;
    char buffer[4096];
    MD5 hash;

    std::ifstream infile(file, std::ios::binary);

    while (infile.good())
    {
        int count = disk.read(infile, buffer, size);
        if (count > 0)
        {
            hash.update(buffer, count);
        }
    }

    hash.finalize();

    return hash.hexdigest();
}
