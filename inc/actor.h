#include "safe_queue.h"
#include <thread>

class Actor
{
public:
    Actor();
    ~Actor();
    void start();
    void stop();
    void set_affinity();
    virtual void run() = 0;

private:
    safe_queue<int> q;
    std::thread t_;
};