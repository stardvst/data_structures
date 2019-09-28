#include <queue>
#include <iostream>
using std::queue;
using std::cout;
using std::endl;

class job
{
    bool success;
    int id;

public:
    job(int jobId, bool shouldWork)
    {
        id = jobId;
        success = shouldWork;
    }

    bool perform()
    {
        cout << "Performing job: " << id << endl;
        return success;
    }
};

void livelock()
{
    queue<job> jobs;
    
    jobs.push(job(1, true));
    jobs.push(job(2, true));
    jobs.push(job(3, false));
    jobs.push(job(4, true));

    while (!jobs.empty())
    {
        // use the 
        job next = jobs.front();
        if (next.perform())
        {
            // if processing was successful, pop it
            // otherwise we'll try it again
            jobs.pop();
        }
    }
}
