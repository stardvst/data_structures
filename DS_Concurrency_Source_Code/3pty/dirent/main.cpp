#include "dirent.h"
#include <iostream>

void process_entry(dirent *entry)
{
    switch (entry->d_type)
    {
    case DT_REG:
        std::cout << "FILE: " << entry->d_name << std::endl;
        break;
    case DT_DIR:
        std::cout << "DIR: " << entry->d_name << std::endl;
        break;
    };
}

void enumerate_dir(const char* root)
{
    dirent *entry;

    DIR *dir = opendir(root);
    if (dir != nullptr)
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            process_entry(entry);
        }

        closedir(dir);
    }
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Expected single command line argument: path" << std::endl;
        return 1;
    }

    enumerate_dir(argv[1]);

    return 0;
}