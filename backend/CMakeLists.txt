cmake_minimum_required(VERSION 3.12)

set(TARGET_NAME backend)
project(${TARGET_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${TARGET_NAME})
set(CMAKE_SKIP_RPATH TRUE)

target_sources(${TARGET_NAME} PRIVATE
  main.cpp
  service.cpp)

include_directories(${TARGET_NAME} ${PROJECT_BINARY_DIR}/../libbackendproto)

target_link_libraries(${TARGET_NAME}
  backendproto
  gRPC::grpc++)
