#ifndef RADAR_ROS_PUBLISHER_HPP
#define RADAR_ROS_PUBLISHER_HPP

#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "radar/serial_handler.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

namespace slamdar {
namespace radar {

class radar_publisher : public rclcpp::Node
{

    radar radar_;
    std::string serial_port_ = "/dev/ttyACM0";
    const unsigned long baudrate_ = 115200;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;

    void timer_callback()
    {
        auto message = std_msgs::msg::String();
        message.data = radar_.readline();
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        std::cout << message.data.c_str();
        publisher_->publish(message);
    }

public:
    radar_publisher() : Node("radar_publisher"), 
                        radar_()
    {
        radar_.open(serial_port_, baudrate_);
        RCLCPP_INFO(this->get_logger(), "Connecting to : '%s'", serial_port_);
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(1ms, std::bind(&radar_publisher::timer_callback, this));
    }

};

}
}



#endif