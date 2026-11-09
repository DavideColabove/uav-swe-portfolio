#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class TelemetryNode {
public:
    TelemetryNode() {
        std::cout << "Initialized TelemetryNode.\n";
    }

    TelemetryNode(const TelemetryNode&) = delete;
    TelemetryNode& operator=(const TelemetryNode&) = delete;

    void run() {
        std::thread prod(&TelemetryNode::sensorReader, this);
        std::thread cons(&TelemetryNode::flightController, this);

        prod.join();
        cons.join();
    }

private:
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<float> telemetry_queue_;
    const float CONST_MULTIPLIER = 3.14;

    void sensorReader() {
        for(int i = 0; i < 5; ++i)
        {
            {
                std::lock_guard<std::mutex>lock(mtx_);
                telemetry_queue_.push(CONST_MULTIPLIER *i);
            }
            cv_.notify_one();
        }
    }

    void flightController() {
        for(int i = 0; i < 5; ++i)
        {
            std::unique_lock<std::mutex> lock(mtx_);
            cv_.wait(lock,[this]{ return !telemetry_queue_.empty();});
            std::cout << telemetry_queue_.front() << std::endl;
            telemetry_queue_.pop();
        }
    }
};

#ifndef UNIT_TEST
int main() {
    TelemetryNode node;
    node.run();
    return 0;
}
#endif