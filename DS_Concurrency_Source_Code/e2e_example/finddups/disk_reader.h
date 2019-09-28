#pragma once
#include <fstream>
#include <mutex>
#include <future>
#include <condition_variable>

class disk_reader
{
    // the number of readers allowed to hit the disk at once
    const int max_readers;

    // the current number of readers
    std::atomic<int> current_readers;

    // serialize access to current_readers to block readers
    std::mutex read_lock;

    // signaled when there is an open reader slot
    std::condition_variable reader_available;

    friend class reader_counter;

    // provides RAII based increment/decrement to ensure that
    // current_readers is balanced even if exceptions are
    // thrown, etc.
    class reader_counter
    {
        disk_reader *disk;

    public:
        reader_counter(disk_reader* d)
            : disk(d)
        {
            disk->current_readers++;
        }

        ~reader_counter()
        {
            disk->current_readers--;
            disk->reader_available.notify_all();
        }
    };

public:
    disk_reader(int max);

    int read(std::ifstream& infile, char *buffer, int buffer_size);
};