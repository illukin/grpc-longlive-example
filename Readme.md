# Build

You should set variables where cmake will find required files:
1. protobuf-config.cmake
2. gRPCConfig.cmake
3. abslConfig.cmake

```
cmake \
-DProtobuf_DIR="" \
-DgRPC_DIR="" \
-Dabsl_DIR="" \
. -B build \
&& cmake --build build
```

# Run backend
```
LD_LIBRARY_PATH=path_to_libbackendproto ./build/backend/backend
```
# Run client
```
build/app
```
