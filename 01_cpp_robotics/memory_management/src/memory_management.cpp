#include <iostream>
#include <memory>
#include <utility>

struct SensorData {  // sample data struct
    float altitude;
    float velocity_z;

    SensorData(float alt, float vz) : altitude(alt), velocity_z(vz) {
        std::cout << "[Allocation] Sensor data packet in memory.\n";
    }
    ~SensorData() { std::cout << "[Dellocation] Packet memory freed.\n"; }
};

void processTelemetry(
    std::unique_ptr<SensorData> data) {  // simulating data computed and ownership transfer
    std::cout << "Data computing... Altitude: " << data->altitude << "m\n";
}  // 'data' out of scope -> destructor

int main() {
    std::unique_ptr<SensorData> imu_packet =
        std::make_unique<SensorData>(120.5f, -2.1f);  // data packet creation using make_unique

    std::cout << "Data acquired. Addess: " << imu_packet.get() << "\n";

    processTelemetry(
        std::move(imu_packet));  // ownership transfer to the processTelemetry function using move

    if (!imu_packet) {
        std::cout
            << "Main pointers now null, ownership transferred.\n";  // verify that the ownership has
                                                                    // been transferred
    }

    return 0;
}