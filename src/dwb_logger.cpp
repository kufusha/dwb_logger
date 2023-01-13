#include "dwb_logger/dwb_logger.hpp"

DwbLogger::DwbLogger(
  const std::string& name_space,
  const rclcpp::NodeOptions& options)
: Node("dwb_logger", name_space, options)
{
  pub_dwb_best_ = this->create_publisher<nav_2d_msgs::msg::Twist2DStamped>(
    "/dwb_best", 10);
  pub_dwb_worst_ = this->create_publisher<nav_2d_msgs::msg::Twist2DStamped>(
    "/dwb_worst", 10);
  sub_dwb_ = this->create_subscription<dwb_msgs::msg::LocalPlanEvaluation>(
    "/evaluation", 10, std::bind(&DwbLogger::dwbCallback, this, std::placeholders::_1));
}

void DwbLogger::dwbCallback(const dwb_msgs::msg::LocalPlanEvaluation::SharedPtr msg)
{
  nav_2d_msgs::msg::Twist2DStamped best_msg, worst_msg;
  
  uint16_t best_index;
  uint16_t worst_index;
  best_index = msg->best_index;
  worst_index = msg->worst_index;
  
  best_msg.header = msg->header;
  best_msg.velocity.x = msg->twists[best_index].traj.velocity.x;
  best_msg.velocity.y = msg->twists[best_index].traj.velocity.y;
  best_msg.velocity.theta = msg->twists[best_index].traj.velocity.theta;
  
  worst_msg.header = msg->header;
  worst_msg.velocity.x = msg->twists[worst_index].traj.velocity.x;
  worst_msg.velocity.y = msg->twists[worst_index].traj.velocity.y;
  worst_msg.velocity.theta = msg->twists[worst_index].traj.velocity.theta;
  
  pub_dwb_best_->publish(best_msg);
  pub_dwb_worst_->publish(worst_msg);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  
  auto node = std::make_shared<DwbLogger>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  
  return 0;
}
