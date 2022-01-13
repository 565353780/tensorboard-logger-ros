cmake_minimum_required(VERSION 3.0.2)
project(tensorboard_logger_ros)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
# set (CMAKE_CXX_STANDARD 17)

find_package(catkin REQUIRED COMPONENTS
  std_msgs
  roscpp
  genmsg
)

find_package(Protobuf REQUIRED)

add_service_files(
  FILES
  ScalarToBool.srv
)

add_message_files(
  FILES
  Scalar.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package()

file(GLOB protos "proto/*.proto")
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${protos})

add_library(tensorboard_logger STATIC
    "src/crc.cc"
    "src/tensorboard_logger.cc"
    ${PROTO_SRCS}
)

target_include_directories(tensorboard_logger
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${Protobuf_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(tensorboard_logger
  PUBLIC
    ${Protobuf_LIBRARIES}
    ${catkin_LIBRARIES}
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_node
  src/tensorboard_logger.cc
  src/TensorBoardLoggerServer.cpp
  src/TensorBoardLoggerServer_node.cpp
)

target_link_libraries(${PROJECT_NAME}_node
  PRIVATE
    tensorboard_logger
)

add_dependencies(${PROJECT_NAME}_node
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_compile_features(${PROJECT_NAME}_node
  PRIVATE
    cxx_std_17
)

add_executable(try_${PROJECT_NAME}
  src/try_TensorBoardLoggerServer.cpp
)

target_link_libraries(try_${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

target_compile_features(try_${PROJECT_NAME}
  PRIVATE
    cxx_std_17
)

add_executable(tensorboard_logger_test
  tests/test_tensorboard_logger.cc
)

target_link_libraries(tensorboard_logger_test
  tensorboard_logger
)

add_dependencies(tensorboard_logger_test
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
)

target_compile_features(tensorboard_logger_test
  PRIVATE
    cxx_std_17
)

