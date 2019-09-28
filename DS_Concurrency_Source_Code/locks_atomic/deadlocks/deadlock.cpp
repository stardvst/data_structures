#include <iostream>
#include <thread>
#include <mutex>
#include <string>
using namespace std;

static mutex db1_mutex;
static mutex db2_mutex;

void simulate_db_usage(string query)
{
    cout << this_thread::get_id() << " " << query << endl;

    std::chrono::milliseconds dura(100);
    std::this_thread::sleep_for(dura);
}

void use_database()
{
    for (int i = 0; i < 10; i++)
    {
        std::lock(db1_mutex, db2_mutex);
        lock_guard<mutex> lock1(db1_mutex, std::adopt_lock);
        lock_guard<mutex> lock2(db2_mutex, std::adopt_lock);

        simulate_db_usage("DB1");
        simulate_db_usage("DB2");
    }
}


void use_database_reverse()
{
    for (int i = 0; i < 10; i++)
    {
        std::lock(db1_mutex, db2_mutex);
        lock_guard<mutex> lock1(db1_mutex, std::adopt_lock);
        lock_guard<mutex> lock2(db2_mutex, std::adopt_lock);

        simulate_db_usage("DB2");
        simulate_db_usage("DB1");
    }
}


void deadlock()
{
    auto t1 = thread(use_database);
    auto t2 = thread(use_database_reverse);

    t1.join();
    t2.join();
}