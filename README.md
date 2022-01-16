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
mkdir -p tb_ws/src
cd tb_ws/src
git clone https://github.com/565353780/tensorboard-logger-ros.git
cd ..
catkin init
catkin config --cmake-args -DCMAKE_CXX_STANDARD=17 -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=Yes
catkin build
```

## Run
```bash
rosrun tensorboard_logger_ros tensorboard_logger_ros_node
rosrun tensorboard_logger_ros try_tensorboard_logger_ros
tensorboard --logdir ./tf_log/ --host 0.0.0.0
```

## Custom Usage

### Add package dependency
add
```bash
tensorboard_logger_ros
```
to CMakeLists.txt in your own package
```bash
find_package(catkin REQUIRED COMPONENTS
    tensorboard_logger_ros
)
```

### Add service client
see
```bash
tensorboard_logger_ros/src/try_TensorBoardLoggerServer.cpp
```

## Enjoy it~

