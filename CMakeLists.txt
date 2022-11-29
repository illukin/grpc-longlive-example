cmake_minimum_required(VERSION 3.12)

set (CMAKE_CXX_STANDARD 17)

project(grpc-longlive)

find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
message(STATUS "Using gRPC ${gRPC_VERSION}")

add_subdirectory(libbackendproto)
add_subdirectory(libclient)
add_subdirectory(backend)

include_directories(${TARGET_NAME}
  ${PROJECT_BINARY_DIR}/libbackendproto
  ${PROJECT_BINARY_DIR}/libclient
  ${PROJECT_SOURCE_DIR}/libclient)

add_executable(app main.cpp)

target_link_libraries(app client)
