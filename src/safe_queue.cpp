#include "safe_queue.h"

template <typename T>
safe_queue<T>::safe_queue(safe_queue<T> &&c)
{
    q = std::move(c.q);
}

template <typename T>
T safe_queue<T>::pop()
{
    // Todo: add mutex
    std::lock_guard<std::mutex> lock(m);
    if (q.empty())
    {
        return {};
    }
    T tmp = q.front();
    q.pop();
    return tmp;
}

template <typename T>
void safe_queue<T>::push(const T &p)
{
    // Todo: add mutex
    std::lock_guard<std::mutex> lock(m);
    q.push(p);
}