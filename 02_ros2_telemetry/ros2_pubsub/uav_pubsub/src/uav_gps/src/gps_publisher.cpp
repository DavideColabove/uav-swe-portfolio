#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "sensor_msgs/msg/nav_sat_fix.hpp"

using namespace std::chrono_literals;

class GpsPublisher : public rclcpp::Node {
public:
    explicit GpsPublisher(const rclcpp::NodeOptions& options) : Node("gps_sensor_node", options) {
        publisher_ = this->create_publisher<sensor_msgs::msg::NavSatFix>("/uav/sensors/gps", 10);
        timer_ = this->create_wall_timer(100ms, [this]() { this->timer_callback(); });
    }

private:
    void timer_callback() {
        auto message = std::make_unique<sensor_msgs::msg::NavSatFix>();
        message->latitude = 45.4;
        message->longitude = 10.9;
        message->altitude = 150.5;

        RCLCPP_INFO(this->get_logger(), "[Pub] Pubblicazione GPS Component...");
        publisher_->publish(std::move(message));
    }

    rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

RCLCPP_COMPONENTS_REGISTER_NODE(GpsPublisher)