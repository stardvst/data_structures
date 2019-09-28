#include "file_enumerator.h"
#include "dirent.h"

#include <memory>

file_enumerator::file_enumerator(std::string root)
{
    // queue the first directory - we'll load it on demand
    directories.push(root);
}

std::string file_enumerator::next_file()
{
    std::string to_return;

    std::lock_guard<std::recursive_mutex> guard(queue_lock);
    if (good())
    {
        to_return = files.front();
        files.pop();
    }

    return to_return;
}

bool file_enumerator::good()
{
    std::lock_guard<std::recursive_mutex> guard(queue_lock);
    load_more();

    // if we have more files, we're good
    return files.size() > 0;
}

void file_enumerator::load_more()
{
    // if we don't have any files but do have directories...
    while (files.size() == 0 && directories.size() > 0)
    {
        // then let's load the next directory
        std::string next_dir = directories.front();
        directories.pop();

        load_dir(next_dir);
    }
}

void file_enumerator::load_dir(const std::string& root)
{
    struct dirent *entry;

    // use custom deleter to make sure closedir is called via RAII
    std::unique_ptr<DIR,std::function<void(DIR*)>> dir(opendir(root.c_str()), [](DIR* d)
    {
        if (d != nullptr)
        {
            closedir(d);
        }
    });

    if (dir != nullptr)
    {
        while ((entry = readdir(dir.get())) != nullptr)
        {
            process_entry(root, entry);
        }
    }
}

void file_enumerator::process_entry(const std::string& root, const dirent* const entry)
{
    // skip things like directories named "."
    if (should_skip(entry))
    {
        return;
    }

    // enumeration is only the file name, so append the path - we need it to 
    // open the file for hashing later
    std::string full_path = root + "/" + entry->d_name;

    switch (entry->d_type)
    {
    case DT_REG:
        files.push(full_path);
        break;
    case DT_DIR:
        directories.push(full_path);
        break;
    };
}

bool file_enumerator::should_skip(const dirent* const entry)
{
    if (entry->d_type == DT_DIR)
    {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            return true;
        }
    }

    return false;
}
