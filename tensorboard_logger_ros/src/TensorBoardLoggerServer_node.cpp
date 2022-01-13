#include "tensorboard_logger_ros/TensorBoardLoggerServer.h"
#include <cstdlib>
#include <ros/init.h>

int main(int argc, char** argv)
{
  std::cout << "Success run TensorBoardLoggerServer!" << std::endl;

  ros::init(argc, argv, "TensorBoardLoggerServer");

  TensorBoardLoggerServer tensorboard_logger_server;

  ros::spin();

  return 1;
}

