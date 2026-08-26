#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include <cmath>

class OdomMonitor : public rclcpp::Node
{
public:
  OdomMonitor() : Node("odom_monitor")
  {
    subscription_ =
        create_subscription<nav_msgs::msg::Odometry>(
            "/odom",
            10,
            [this](nav_msgs::msg::Odometry::ConstSharedPtr message)
            {
              odom_callback(message);
            });

    RCLCPP_INFO(get_logger(), "里程计监控节点已启动");
  }

private:
  void odom_callback(
      nav_msgs::msg::Odometry::ConstSharedPtr message)
  {
    double x = message->pose.pose.position.x;
    double y = message->pose.pose.position.y;

    if (!has_previous_pose_)
    {
      previous_x_ = x;
      previous_y_ = y;
      has_previous_pose_ = true;

      RCLCPP_INFO(
          get_logger(),
          "记录初始位置：x=%.3f, y=%.3f",
          x,
          y);

      return;
    }

    double dx = x - previous_x_;
    double dy = y - previous_y_;

    total_distance_ += std::hypot(dx, dy);

    previous_x_ = x;
    previous_y_ = y;

   RCLCPP_INFO_THROTTLE(
    get_logger(),
    *get_clock(),
    1000,
    "x=%.3f, y=%.3f, total=%.3f m",
    x,
    y,
    total_distance_);

  }
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_;
  bool has_previous_pose_{false};
  double previous_x_{0.0};
  double previous_y_{0.0};
  double total_distance_{0.0};
};
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std ::make_shared<OdomMonitor>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
