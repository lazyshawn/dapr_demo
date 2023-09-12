/*
* 1. 定义 gRPC 服务: return(a+b)
* 1. 启动 gRPC 服务，监听 5001 端口
* @gRPC:
* build/src/grpc_svr
* @Dapr :
* dapr run --app-id server --app-port 5001 --app-protocol grpc build/src/grpc_svr
*/

#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

void Run();

int main(int argc, char **argv) {
  Run();
  return 0;
}

// 定义服务内容
class MathTestSvrImpl final : public mathtest::MathTest::Service {
  grpc::Status sendRequest(grpc::ServerContext *context, const mathtest::MathRequest *request, mathtest::MathReply *reply) override {
    int a = request->a();
    int b = request->b();

    reply->set_result(a * b);

    return grpc::Status::OK;
  }
};

// 启动服务
void Run() {
  std::string address("0.0.0.0:5001");
  MathTestSvrImpl service;

  grpc::ServerBuilder builder;

  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on port: " << address << std::endl;

  server->Wait();
}
