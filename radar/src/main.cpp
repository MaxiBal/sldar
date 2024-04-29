#include "radar/ros_publisher.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<slamdar::radar::radar_publisher>());
  rclcpp::shutdown();
  return 0;
}