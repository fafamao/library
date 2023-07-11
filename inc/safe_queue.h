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
    safe_queue(safe_queue<T> &&c) {
        q = std::move(c.q);
    }

    ~safe_queue() {};

    T pop() {
        std::lock_guard<std::mutex> lock(m);
        if (q.empty())
        {
            return {};
        }
        T tmp = q.front();
        q.pop();
        return tmp;
    }

    void push(const T &p) {
        std::lock_guard<std::mutex> lock(m);
        q.push(p);
    }

    unsigned long size() {
        std::lock_guard<std::mutex> lock(m);
        return q.size();
    }
};