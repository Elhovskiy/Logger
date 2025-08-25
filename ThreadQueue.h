#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadQueue {
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(value);
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{ return !q.empty(); });
        T value = q.front();
        q.pop();
        return value;
    }

private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
};

