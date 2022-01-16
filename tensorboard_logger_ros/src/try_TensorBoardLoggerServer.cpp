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

  tensorboard_logger_ros::ScalarToBool tensorboard_logger_serve;

  for(size_t i = 0; i < 100; ++i)
  {
    tensorboard_logger_serve.request.scalar.name = "test_log";
    tensorboard_logger_serve.request.scalar.step = i;
    tensorboard_logger_serve.request.scalar.value = 1000.0 * i;

    if (!try_tensorboard_logger_client.call(tensorboard_logger_serve))
    {
      std::cout << "call tensorboard_logger_server failed!\n";

      return -1;
    }

    if(!tensorboard_logger_serve.response.success)
    {
      std::cout << "tensorboard_logger_server log failed!\n";

      return -1;
    }
  }

  return 0;
}

