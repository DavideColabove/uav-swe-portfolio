#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<float> telemetry_queue;
const float CONST_MULTIPLIER = 3.14;

void sensorReader() {  // 'producer' function
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);  // using lock_guard to lock the variable
            telemetry_queue.push(CONST_MULTIPLIER * i);
        }
        cv.notify_one();
    }
}

void flightController() {  // controller function
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(
            mtx);  // using unique_lock to enable temporary lock/unlock
        cv.wait(lock, [] { return !telemetry_queue.empty(); });  // handles spurious wakeups
        std::cout << telemetry_queue.front() << "\n";
        telemetry_queue.pop();
    }
}

int main() {
    std::thread t1(sensorReader);
    std::thread t2(flightController);

    t1.join();
    t2.join();

    return 0;
}