cmake_minimum_required(VERSION 3.12)

set (CMAKE_CXX_STANDARD 17)

set(TARGET_NAME backendproto)
project(${TARGET_NAME})

set(CMAKE_SKIP_RPATH TRUE)

set(PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
set(GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Файлы *.proto
get_filename_component(BACKEND "${PROJECT_SOURCE_DIR}/backend.proto" ABSOLUTE)

# Формирование списка генерируемых исходных файлов protobuf и grpc
foreach(_filename backend)
  foreach(_extension .pb.cc .pb.h .grpc.pb.cc .grpc.pb.h)
    list(APPEND GENERATED_SRCS ${PROJECT_BINARY_DIR}/${_filename}${_extension})
  endforeach()
endforeach()

add_custom_command(
  OUTPUT ${GENERATED_SRCS}
  COMMAND ${PROTOBUF_PROTOC}
  ARGS --grpc_out "${PROJECT_BINARY_DIR}"
  --cpp_out "${PROJECT_BINARY_DIR}"
  -I "${PROJECT_SOURCE_DIR}"
  --plugin=protoc-gen-grpc="${GRPC_CPP_PLUGIN_EXECUTABLE}"
  "${BACKEND}"
  DEPENDS "${BACKEND}")

add_library(${TARGET_NAME} SHARED
  ${GENERATED_SRCS})

target_link_libraries(${TARGET_NAME}
  protobuf::libprotobuf
  gRPC::grpc++)
