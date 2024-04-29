#ifndef LIDAR_ROS_PUBLISHER_HPP
#define LIDAR_ROS_PUBLISHER_HPP

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "lidar.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

#define LIDAR_BUF_SIZE 10000

constexpr float brad_to_rad(float angle)
{
    return angle * 3.14f / (16384.f * 2);
}

namespace slamdar {
namespace lidar {

class lidar_publisher : public rclcpp::Node
{

    lidar lidar_;

    sl_lidar_response_measurement_node_hq_t buf[LIDAR_BUF_SIZE];

    std::string serial_port_ = "/dev/ttyACM0";
    const unsigned long baudrate_ = 115200;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        
        // read in lidar data

        lidar_.update_scan(buf);

        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        std::cout << message.data.c_str();
        publisher_->publish(message);
    }

public:
    radar_publisher() : Node("lidar_publisher"), 
                        lidar_()
    {
        auto lidar_device_info = lidar_.get_device_info();

        RCLCPP_INFO(this->get_logger(), "Connected to LIDAR: '%d'", lidar_device_info.model);
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(1ms, std::bind(&radar_publisher::timer_callback, this));
    }

};

}
}



#endif