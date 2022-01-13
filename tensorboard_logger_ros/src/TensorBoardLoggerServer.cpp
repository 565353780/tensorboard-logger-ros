#include "tensorboard_logger_ros/TensorBoardLoggerServer.h"

bool TensorBoardLoggerServer::logScalarCallback(
    tensorboard_logger_ros::ScalarToBool::Request &req,
    tensorboard_logger_ros::ScalarToBool::Response &res)
{
  std::cout << "Start TensorBoardLogger serve!" << std::endl;

  const std::string name = req.scalar.name;
  const size_t step = req.scalar.step;
  const double value = req.scalar.value;
  tensorboard_logger_->add_scalar(name, step, value);

  res.success = true;

  // std_msgs::Bool log_state;
  // log_state.data = res.success;
  // tensorboard_logger_pub_.publish(log_state);

  return true;
}

