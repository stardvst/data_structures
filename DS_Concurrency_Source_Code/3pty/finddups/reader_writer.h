#pragma once

#include <mutex>
#include <atomic>
#include <condition_variable>

class reader_writer_lock
{
private:
    std::mutex reader_lock;
    std::mutex writer_lock;
    std::mutex count_lock;

    std::condition_variable writers_done_cv;

    std::atomic<int> reader_count = 0;

    std::atomic<int> writers_waiting = 0;
    std::atomic<int> readers_waiting = 0;

public:
    template<class predicate>
    void read(predicate pred)
    {
        {
            readers_waiting++;

            std::unique_lock<std::mutex> writer_guard(writer_lock);
            writers_done_cv.wait(writer_guard, [&]{ return writers_waiting < readers_waiting; });

            // the writers got their chance - so let's read now...
            std::unique_lock<std::mutex> reader_guard(reader_lock);
            std::unique_lock<std::mutex> count_guard(count_lock);

            readers_waiting--;
            reader_count++;
        }

        pred();

        {
            std::unique_lock<std::mutex> count_guard(count_lock);
            reader_count--;
        }
    }

    template<class predicate>
    void write(predicate pred)
    {
        {
            writers_waiting++;

            // take the reader lock
            std::unique_lock<std::mutex> writer_guard(writer_lock);

            writers_waiting--;

            // at this point we hold the reader lock and we know there are
            // no readers - so we can safely write.
            pred();
            
            writers_done_cv.notify_all();
        }
    }
};