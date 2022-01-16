#ifndef TENSORBOARD_LOGGER_SERVER_H
#define TENSORBOARD_LOGGER_SERVER_H

#include <iostream>
#include <ctime>
#include <fstream>
#include <dirent.h>
#include <cstdlib>

#include <ros/ros.h>
#include <std_msgs/Bool.h>

#include <tensorboard_logger_ros/tensorboard_logger.h>
#include <tensorboard_logger_ros/Scalar.h>
#include <tensorboard_logger_ros/ScalarToBool.h>

class TensorBoardLoggerServer
{
public:
  TensorBoardLoggerServer() :
    tensorboard_logger_server_(nh_.advertiseService("tensorboard_logger/log_scalar",
                                 &TensorBoardLoggerServer::logScalarCallback, this)),
    tensorboard_logger_pub_(nh_.advertise<std_msgs::Bool>("tensorboard_logger/log_state", queue_size_))
  {
    std::string log_prefix =
      std::string(std::getenv("HOME")) +
      "/.ros/RUN_LOG/TensorBoardLoggerServer/";

    std::time_t now = time(0);
    tm* ltm = localtime(&now);
    std::string log_date = std::to_string(1900 + ltm->tm_year) + "_";
    log_date += std::to_string(1 + ltm->tm_mon) + "_";
    log_date += std::to_string(ltm->tm_mday) + "_";
    log_date += std::to_string(ltm->tm_hour) + "-";
    log_date += std::to_string(ltm->tm_min) + "-";
    log_date += std::to_string(ltm->tm_sec);

    log_prefix += log_date + "/";

    std::string log_file_path = log_prefix + "tfevents.pb";
    std::cout << "log_file_path = " << log_file_path << std::endl;

    if(opendir(log_prefix.c_str()) == NULL)
    {
      system(("mkdir -p " + log_prefix).c_str());
    }

    std::ofstream read_file;
    read_file.open(log_file_path, std::ios::app);
    if(!read_file)
    {
      system(("touch " + log_file_path).c_str());
    }
    else
    {
      std::cout << "file exists at : " << log_file_path << std::endl;
      read_file.close();
    }

    tensorboard_logger_ = new TensorBoardLogger(log_file_path.c_str());
  }

  ~TensorBoardLoggerServer()
  {
    delete(tensorboard_logger_);
  }

  bool logScalarCallback(
      tensorboard_logger_ros::ScalarToBool::Request &req,
      tensorboard_logger_ros::ScalarToBool::Response &res);

private:
  ros::NodeHandle nh_;

  uint32_t queue_size_ = 1;
  ros::ServiceServer tensorboard_logger_server_;
  ros::Publisher tensorboard_logger_pub_;

  TensorBoardLogger* tensorboard_logger_;
};

#endif // TENSORBOARD_LOGGER_SERVER_H
