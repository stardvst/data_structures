#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>

template<typename _T>
class blocking_queue
{
private:
    std::mutex lock;
    std::queue<_T> data;
    std::condition_variable notify;

public:
void enqueue(_T& value)
{
    std::unique_lock<std::mutex> guard(lock);

    data.push(value);

    guard.unlock();

    notify.notify_one();
}
void deque(_T& value)
{
    std::unique_lock<std::mutex> guard(lock);

    notify.wait(guard, [this]{return !data.empty(); });

    value = data.front();

    data.pop();
}

bool try_deque(_T& value, 
               const std::chrono::milliseconds &duration)
{
    std::unique_lock<std::mutex> guard(lock);

    bool notified = notify.wait_for(guard, duration, 
                                    [this]{return !data.empty(); });

    if (notified)
    {
        value = data.front();
        data.pop();
    }

    return notified;
}
};

//bool try_deque(_T& value)
//{
//    std::lock_guard<std::mutex> guard(lock);
//    if (data.empty())
//    {
//        return false;
//    }

//    value = data.front();
//    data.pop();

//    return true;
//}
