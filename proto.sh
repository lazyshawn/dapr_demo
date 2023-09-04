#!/bin/bash
# @brief: create grpc protocol source files

protoc -I proto --cpp_out=proto/src --grpc_out=proto/src --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` mathtest.proto
