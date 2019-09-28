#include <thread>

#include "dup_search.h"
#include "file_hasher.h"
#include "file_enumerator.h"

dup_search::dup_search(std::string root)
    : enumerator(root)
{
}

// starts the thread scheduler which will manage the
// process asynchronously allowing begin to return immediately
void dup_search::begin()
{
    // prevent begin from being called multiple times.
    if (!started)
    {
        std::lock_guard<std::mutex> begin_guard(started_mutex);
        if (started)
        {
            return;
        }

        started = true;
    }

    scheduler = std::async(&dup_search::thread_scheduler, this);
}

void dup_search::thread_scheduler()
{
    // how many hashing threads?  At least one, but no more than our max concurrency
    unsigned int thread_count = std::max<unsigned int>(std::thread::hardware_concurrency(), 1);

    // start the hashing threads
    for (unsigned int i = 0; i < thread_count; i++)
    {
        hashers.push_back(std::async(&dup_search::hash_files, this));
    }

    // wait for the hashers to finish
    for (std::future<void>& hasher : hashers)
    {
        hasher.wait();
    }

    // and trim the non-duplicates - since this is the last
    // thing we do, and we're already on our own thread,
    // we can just do this on the current thread
    trim();
}

// while there are unhashed files... hash them
void dup_search::hash_files()
{
    // file_enumerator is thread-safe
    while (enumerator.good())
    {
        std::string file = enumerator.next_file();

        if (!file.empty())
        {
            process_file(file);
        }
    }
}

// hash the file and update the map of duplicates
void dup_search::process_file(const std::string& file)
{
    std::string digest = file_hasher::get_md5_hash(file);

    std::lock_guard<std::mutex> map_guard(entries_lock);

    // if we had map<string,duplicate> we could do this:
    // entries[digest].push_back(file);

    // Item 24 - Effective STL (Scott Meyers)
    // If a duplicate with our hash already exists in the map then this
    // will find it, otherwise it will find the appropriate location for an 
    // emplace_hint - this avoids traversing the map twice
    auto lb_existing = entries.lower_bound(digest);
    if (lb_existing != entries.end() && !(entries.key_comp()(digest, lb_existing->first)))
    {
        lb_existing->second->duplicates.push_back(file);
    }
    else
    {
        entries.emplace_hint(lb_existing, digest,
            std::unique_ptr<duplicate>(new duplicate(digest, file)));
    }
}

// removes any non-duplicate entries from the map
// should only be called once hashing is complete
void dup_search::trim()
{
    auto iter = entries.begin();
    auto end = entries.end();

    for (; iter != end;)
    {
        if (iter->second->duplicates.size() <= 1)
        {
            entries.erase(iter++);
        }
        else
        {
            ++iter;
        }
    }
}

// waits for the process to complete and invokes the predicate
// for each duplicate 
void dup_search::get(std::function<void(const duplicate* const dup)> pred)
{
    if (scheduler.valid())
    {
        // the scheduler will terminate when the results are ready
        scheduler.wait();

        for (auto& entry : entries)
        {
            pred(entry.second.get());
        }
    }
}
