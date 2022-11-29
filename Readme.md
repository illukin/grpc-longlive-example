# Build

If `Protobuf` and `gRPC` are not installed in your system, you should build it
manually and set variables where cmake will find required files:
1. protobuf-config.cmake
2. gRPCConfig.cmake
3. abslConfig.cmake

```
cmake \
-DProtobuf_DIR=/path/to/protobuf-config.cmake \
-DgRPC_DIR=/path/to/gRPCConfig.cmake \
-Dabsl_DIR=/path/to/abslConfig.cmake \
. -B build \
&& cmake --build build
```

# Run backend
```
LD_LIBRARY_PATH=/path/to/libbackendproto ./build/backend/backend
```
# Run client
```
build/app
```
