#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "uav_interfaces/msg/drone_telemetry.hpp"

using namespace std::chrono_literals;

class GpsPublisher : public rclcpp::Node {
public:
    explicit GpsPublisher(const rclcpp::NodeOptions& options) : Node("gps_sensor_node", options) {
        rclcpp::QoS qos_profile = rclcpp::SensorDataQoS();

        publisher_ = this->create_publisher<uav_interfaces::msg::DroneTelemetry>(
            "/uav/sensors/telemetry", qos_profile);

        timer_ = this->create_wall_timer(100ms, std::bind(&GpsPublisher::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "GPS Component launched with QoS: SensorData.");
    }

private:
    void timer_callback() {
        auto msg = std::make_unique<uav_interfaces::msg::DroneTelemetry>();

        msg->header.stamp = this->get_clock()->now();
        msg->header.frame_id = "gps_link";
        msg->battery_percentage = 85;
        msg->latitude = 45.123456;
        msg->longitude = 9.654321;
        msg->altitude = 120.5;
        msg->velocity_x = 5.2;
        msg->velocity_y = 0.0;
        msg->velocity_z = -0.1;
        msg->flight_mode = 1;  // OFFBOARD

        RCLCPP_INFO(this->get_logger(), "Telemetry: (Lat: %.4f, Lon: %.4f, Alt: %.1f)",
                    msg->latitude, msg->longitude, msg->altitude);

        publisher_->publish(std::move(msg));
    }

    rclcpp::Publisher<uav_interfaces::msg::DroneTelemetry>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

RCLCPP_COMPONENTS_REGISTER_NODE(GpsPublisher)