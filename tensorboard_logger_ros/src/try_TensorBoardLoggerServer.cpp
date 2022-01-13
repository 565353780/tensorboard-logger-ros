#include <ros/ros.h>
#include <iostream>

#include "tensorboard_logger_ros/ScalarToBool.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "try_TensorBoardLoggerServer");

  ros::NodeHandle nh;
  ros::ServiceClient try_tensorboard_logger_client =
      nh.serviceClient<tensorboard_logger_ros::ScalarToBool>("tensorboard_logger/log_scalar");

  std::cout << "Start call tensorboard_logger service..." << std::endl;

  tensorboard_logger_ros::ScalarToBool log_tensorboard_logger_serve;

  for(size_t i = 0; i < 100; ++i)
  {
    log_tensorboard_logger_serve.request.scalar.name = "test_log";
    log_tensorboard_logger_serve.request.scalar.step = i;
    log_tensorboard_logger_serve.request.scalar.value = 1000.0 * i;

    if (!try_tensorboard_logger_client.call(log_tensorboard_logger_serve))
    {
      std::cout << "call tensorboard_logger_server failed!" << std::endl;

      return -1;
    }

    std::cout << "Get tensorboard_logger_server response : " <<
      log_tensorboard_logger_serve.response.success << " !" << std::endl;
  }

  return 0;
}

