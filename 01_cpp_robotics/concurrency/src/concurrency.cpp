#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
float drone_altitude = 0;

void sensorReader() {
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            drone_altitude += drone_altitude + i;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

void flightController() {
    for (int i = 0; i < 10; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            std::cout << drone_altitude << "\n";
        }
        std::this_thread::sleep_for(std::chrono::microseconds(500));
    }
}

int main() {
    std::thread t1(sensorReader);
    std::thread t2(flightController);

    t1.join();
    t2.join();

    return 0;
}