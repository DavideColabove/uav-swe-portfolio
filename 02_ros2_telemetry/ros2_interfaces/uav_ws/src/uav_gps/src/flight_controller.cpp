#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "uav_interfaces/msg/drone_telemetry.hpp"

class FlightController : public rclcpp::Node {
public:
    FlightController() : Node("flight_controller_node") {
        
        rclcpp::QoS qos_profile = rclcpp::SensorDataQoS();

        subscription_ = this->create_subscription<uav_interfaces::msg::DroneTelemetry>(
            "/uav/sensors/telemetry", qos_profile,
            std::bind(&FlightController::telemetry_callback, this, std::placeholders::_1));
            
        RCLCPP_INFO(this->get_logger(), "Flight Controller in ascolto su /uav/sensors/telemetry (QoS: Best Effort)");
    }

private:
    void telemetry_callback(const uav_interfaces::msg::DroneTelemetry::SharedPtr msg) const {
        RCLCPP_INFO(this->get_logger(), "Telemetry received - Battery: %d%%, Altitude: %.1fm", 
                    msg->battery_percentage, msg->altitude);
    }

    rclcpp::Subscription<uav_interfaces::msg::DroneTelemetry>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FlightController>());
    rclcpp::shutdown();
    return 0;
}