cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME client)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SKIP_RPATH TRUE)

add_library(${TARGET_NAME} SHARED
  client.cpp)

include_directories(${TARGET_NAME} ${PROJECT_BINARY_DIR}/../libbackendproto)

target_link_libraries(${TARGET_NAME}
  backendproto
  gRPC::grpc++)
