#pragma once

#include <string>
#include <map>
#include <mutex>
#include <atomic>
#include <functional>
#include <memory>
#include <future>

#include "duplicate.h"
#include "file_enumerator.h"

class dup_search
{
    // the shared file enumerator
    file_enumerator enumerator;

    // prevent begin from being called multiple times
    std::mutex started_mutex;
    std::atomic<bool> started = false;

    // hasher threads
    std::list<std::future<void>> hashers;

    // scheduler thread
    std::future<void> scheduler;

    // map<[file hash], [duplicate file information]>
    std::map<std::string, std::unique_ptr<duplicate>> entries;

    // serializes access to the entries map
    std::mutex entries_lock;

    // hashes a file and adds to the entries map
    void process_file(const std::string& file);

    // deques files from files_to_process queue and processes them
    void hash_files();

    // schedules the background threads
    void thread_scheduler();

    // trims the non-duplicates from the map
    void trim();

public:
    dup_search(std::string root);

    // begins the hashing process
    void begin();

    // waits until the process is complete and 
    // executes the provided callback for each duplicate
    void get(std::function<void(const duplicate* const dup)> pred);
};