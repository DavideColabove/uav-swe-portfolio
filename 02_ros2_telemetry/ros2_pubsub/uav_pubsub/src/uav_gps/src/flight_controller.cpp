#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"

class FlightController : public rclcpp::Node {
public:
    FlightController() : Node("flight_controller_node") {
        subscription_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
            "/uav/sensors/gps", 10, [this](std::unique_ptr<sensor_msgs::msg::NavSatFix> msg) {
                this->gps_callback(std::move(msg));
            });
    }

private:
    void gps_callback(std::unique_ptr<sensor_msgs::msg::NavSatFix> msg) const {
        RCLCPP_INFO(this->get_logger(), "Received: Lat: %f, Lon: %f, Alt: %f", msg->latitude,
                    msg->longitude, msg->altitude);
    }

    rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr subscription_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);

    auto execut = std::make_shared<FlightController>();
    rclcpp::spin(execut);

    rclcpp::shutdown();
    return 0;
}