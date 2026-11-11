#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <atomic>
#include <optional>
#include <array>

// 1. SPSC Ring Buffer (Senza alignas per evitare corruzione dello stack)
template <typename T, size_t Capacity>
class SpscRingBuffer {
    static_assert((Capacity != 0) && ((Capacity & (Capacity - 1)) == 0), 
                  "La capacità deve essere una potenza di due");
public:
    SpscRingBuffer() : head_(0), tail_(0) {}
    
    bool push(const T& item) {
        size_t current_head = head_.load(std::memory_order_relaxed);
        size_t current_tail = tail_.load(std::memory_order_acquire);
        size_t next_head = (current_head + 1) & (Capacity - 1);
        if (next_head == current_tail) return false; 
        buffer_[current_head] = item;
        head_.store(next_head, std::memory_order_release);
        return true; 
    }
    
    std::optional<T> pop() {
        size_t current_tail = tail_.load(std::memory_order_relaxed);
        size_t current_head = head_.load(std::memory_order_acquire);
        if (current_head == current_tail) return std::nullopt;
        T item = buffer_[current_tail];
        size_t next_tail = (current_tail + 1) & (Capacity - 1);
        tail_.store(next_tail, std::memory_order_release);
        return item;
    }
private:
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
    std::array<T, Capacity> buffer_;
};

// 2. Mutex Queue
#include <queue>
#include <mutex>
template <typename T>
class MutexQueue {
public:
    explicit MutexQueue(size_t capacity) : capacity_(capacity) {}
    bool push(const T& item) {
        std::lock_guard<std::mutex> lock(mtx_);
        if (queue_.size() >= capacity_) return false;
        queue_.push(item);
        return true;
    }
    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (queue_.empty()) return std::nullopt;
        T item = queue_.front();
        queue_.pop();
        return item;
    }
private:
    std::queue<T> queue_;
    size_t capacity_;
    std::mutex mtx_;
};

constexpr int NUM_ITEMS = 250000;
constexpr size_t QUEUE_CAPACITY = 1024;

struct Payload {
    uint64_t id;
    uint64_t timestamp_ns;
    double data[8];
};

template <typename QueueType>
void run_benchmark(QueueType& queue, const std::string& name, std::ofstream& csv_file) {
    std::vector<uint64_t> latencies;
    latencies.reserve(NUM_ITEMS);
    
    std::cout << "\n[" << name << "] Avvio test..." << std::endl;
    auto start_time = std::chrono::steady_clock::now();

    std::thread producer([&]() {
        for (int i = 0; i < NUM_ITEMS; ++i) {
            Payload p; 
            p.id = i;
            p.timestamp_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
            
            while (!queue.push(p)) {
                std::this_thread::yield(); 
            }
        }
    });

    std::thread consumer([&]() {
        for (int i = 0; i < NUM_ITEMS; ++i) {
            std::optional<Payload> p;
            while (true) {
                p = queue.pop();
                if (p.has_value()) break;
                std::this_thread::yield();
            }
            uint64_t now = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::steady_clock::now().time_since_epoch()).count();
            latencies.push_back(now - p->timestamp_ns);
        }
    });

    producer.join();
    consumer.join();

    auto end_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    double throughput = NUM_ITEMS / diff.count();

    size_t p99_index = latencies.size() * 0.99;
    std::nth_element(latencies.begin(), latencies.begin() + p99_index, latencies.end());
    uint64_t p99_latency_ns = latencies[p99_index];

    std::cout << "[" << name << "] Throughput: " << throughput 
              << " ops/sec, p99 Latency: " << p99_latency_ns << " ns" << std::endl;
    
    csv_file << name << "," << throughput << "," << p99_latency_ns << "\n";
}

int main() {
    std::ofstream csv_file("results/queue_bench.csv");
    if (!csv_file.is_open()) return 1;
    csv_file << "Queue_Type,Throughput_ops_sec,p99_Latency_ns\n";

    SpscRingBuffer<Payload, QUEUE_CAPACITY> lock_free_queue;
    run_benchmark(lock_free_queue, "LockFree", csv_file);

    MutexQueue<Payload> mutex_queue(QUEUE_CAPACITY);
    run_benchmark(mutex_queue, "Mutex", csv_file);

    std::cout << "\nCompletato con successo!" << std::endl;
    return 0;
}