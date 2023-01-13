#include <rclcpp/rclcpp.hpp>
#include <dwb_msgs/msg/local_plan_evaluation.hpp>
#include <nav_2d_msgs/msg/twist2_d_stamped.hpp>

class DwbLogger : public rclcpp::Node
{
public:
  DwbLogger(
    const std::string& name_space = "",
    const rclcpp::NodeOptions& options = rclcpp::NodeOptions());
    
private:
  void dwbCallback(const dwb_msgs::msg::LocalPlanEvaluation::SharedPtr msg);
  
  rclcpp::Publisher<nav_2d_msgs::msg::Twist2DStamped>::SharedPtr pub_dwb_best_;
  rclcpp::Publisher<nav_2d_msgs::msg::Twist2DStamped>::SharedPtr pub_dwb_worst_;
  rclcpp::Subscription<dwb_msgs::msg::LocalPlanEvaluation>::SharedPtr sub_dwb_;
};
