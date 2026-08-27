#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

class VelocityPublisher : public rclcpp::Node
{
public:
  VelocityPublisher()
  : Node("velocity_publisher")
  {
    publisher_ =
      create_publisher<geometry_msgs::msg::Twist>(
      "/patrol/cmd_vel_test", 10);
    declare_parameter<double>("linear_speed", 0.05);
    declare_parameter<double>("angular_speed", 0.1);
    timer_ = create_wall_timer(
      std::chrono::milliseconds(100),
      [this]()
      {
        publish_velocity();
      });

    RCLCPP_INFO(get_logger(), "速度发布节点已启动");
  }

private:
  void publish_velocity()
  {
    geometry_msgs::msg::Twist message;

    if (publish_count_ < 30) {
      message.linear.x =
        get_parameter("linear_speed").as_double();

      message.angular.z =
        get_parameter("angular_speed").as_double();
    } else {
      message.linear.x = 0.0;
      message.angular.z = 0.0;
    }

    publisher_->publish(message);
    ++publish_count_;
  }
  int publish_count_{0};
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<VelocityPublisher>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
