# TensorBoard Logger ROS

Support `scalar`, `histogram`, `image`, `audio` `text` and `projector`.

## Install

```bash
sudo apt install libprotobuf-dev protobuf-compiler
```

## Build

### Use CMake
```bash
mkdir build && cd build && cmake .. && cmake --build . -j
cd .. && mkdir demo && ./tensorboard_logger_test
tensorboard --logdir ./ --host 0.0.0.0
```

### Use Catkin

```bash
catkin build
rosrun tensorboard_logger_ros tensorboard_logger_ros_node
rosrun tensorboard_logger_ros try_tensorboard_logger_ros
tensorboard --logdir ./tf_log/ --host 0.0.0.0
```

## Enjoy it~

