#pragma once
#include <condition_variable>
#include <cstddef>
#include <mutex>
#include <optional>
#include <queue>

template <typename T>
class MutexQueue {
public:
    explicit MutexQueue(size_t capacity) : capacity_(capacity) {}

    // 1. Metodo non-bloccante per il benchmark (spin-wait)
    bool push(const T& item) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (queue_.size() >= capacity_) {
            return false;  // Coda piena
        }
        queue_.push(item);
        cv_.notify_one();  // Notifica eventuali thread in attesa
        return true;
    }

    // 2. Metodo non-bloccante per il benchmark (spin-wait)
    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (queue_.empty()) {
            return std::nullopt;  // Coda vuota
        }
        T item = queue_.front();
        queue_.pop();
        return item;
    }

    // 3. Il tuo metodo bloccante originale con condition_variable (Topic 1.2)
    T wait_and_pop() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this] { return !queue_.empty(); });
        T item = queue_.front();
        queue_.pop();
        return item;
    }

private:
    std::queue<T> queue_;
    size_t capacity_;
    std::mutex mtx_;
    std::condition_variable cv_;
};