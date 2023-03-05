#include <queue>
#include <mutex>

template <typename T>

class safe_queue
{
public:
    std::queue<T> q;
    mutable std::mutex m;

    safe_queue() = default;
    safe_queue(const safe_queue &) = delete;
    safe_queue &operator=(const safe_queue<T> &) = delete;
    safe_queue(safe_queue<T> &&);

    T pop();
    void push(const T &);
};