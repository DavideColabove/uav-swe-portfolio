#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;
float drone_altitude = 0;

void sensorReader() {  // 'producer' function
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);  // using lock_guard to lock the variable
            drone_altitude += drone_altitude + i;
            data_ready = true;
        }
        cv.notify_one();
    }
}

void flightController() {  // controller function
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::mutex> lock(
            mtx);  // using unique_lock to enable temporary lock/unlock
        cv.wait(lock, [] { return data_ready; });  // handles spurious wakeups
        std::cout << drone_altitude << "\n";
        data_ready = false;  // flag reset
    }
}

int main() {
    std::thread t1(sensorReader);
    std::thread t2(flightController);

    t1.join();
    t2.join();

    return 0;
}