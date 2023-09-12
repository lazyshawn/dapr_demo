✨ dapr_demo
------------

✨ Build
--------
1. Build grpc protocol.
```bash
# linux
# protoc -I proto --cpp_out=proto/src --grpc_out=proto/src --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` mathtest.proto
bash ./proto.sh
# win32
# cd <grpc/bin>
# ./protoc -I proto --cpp_out=proto/src --grpc_out=proto/src --plugin=protoc-gen-grpc=./grpc_cpp_plugin.exe mathtest.proto
```


