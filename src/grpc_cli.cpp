/*
* @gRPC client:
* 1. 启用 gRPC 客户端，端口号绑定到服务端的监听端口
* @Dapr client:
* 1. 启用 gRPC 客户端，端口号绑定到 sidecar 的 dapr-grpc-port
* 1. 在发送请求时，通过 grpc::ClientContext 添加服务端的 app-id
* 1. dapr run --app-id client --dapr-grpc-port 50001 -- build/src/grpc_cli
*/

#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

#include <string>

void Run(int port);
class MathTestCliImpl;

int main(int argc, char **argv) {
  size_t port = 5001;
  if (argc == 2) {
    port = atof(argv[1]);
  }
  Run(port);
  return 0;
}

class MathTestCliImpl {
public:
  // 使用 channel 初始化 stub
  MathTestCliImpl(std::shared_ptr<grpc::Channel> channel) : stub_(mathtest::MathTest::NewStub(channel)) {}

  int sendRequest(int a, int b) {
    mathtest::MathRequest request;

    request.set_a(a);
    request.set_b(b);

    mathtest::MathReply reply;

    // Tells Dapr to discover and invoke an app named "server"
    grpc::ClientContext context;
    context.AddMetadata("dapr-app-id", "server");

    grpc::Status status = stub_->sendRequest(&context, request, &reply);

    if (status.ok()) {
      return reply.result();
    } else {
      std::cout << status.error_code() << ": " << status.error_message() << std::endl;
      return -1;
    }
  }

private:
  std::unique_ptr<mathtest::MathTest::Stub> stub_;
};

void Run(int port) {
  // 客户端地址
  std::string address = "0.0.0.0:" + std::to_string(port);
  printf("Send request to: %s\n", address.c_str());
  MathTestCliImpl client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

  int response;

  int a = 5, b = 10;
  response = client.sendRequest(a, b);
  std::cout << "Answer received: " << a << " * " << b << " = " << response << std::endl;
}
