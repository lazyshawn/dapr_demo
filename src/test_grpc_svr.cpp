#include <string>

#include "mathtest.grpc.pb.h"
#include <grpcpp/grpcpp.h>

void Run();

int main(int argc, char **argv) {
  Run();
  return 0;
}

class MathTestSvrImpl final : public mathtest::MathTest::Service {
  grpc::Status sendRequest(grpc::ServerContext *context, const mathtest::MathRequest *request, mathtest::MathReply *reply) override {
    int a = request->a();
    int b = request->b();

    reply->set_result(a * b);

    return grpc::Status::OK;
  }
};

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
