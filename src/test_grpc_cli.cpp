#include <string>

#include "mathtest.grpc.pb.h"
#include <grpcpp/grpcpp.h>

void Run();
class MathTestCliImpl;

int main(int argc, char **argv) {
  Run();
  return 0;
}

class MathTestCliImpl {
public:
  MathTestCliImpl(std::shared_ptr<grpc::Channel> channel) : stub_(mathtest::MathTest::NewStub(channel)) {}

  int sendRequest(int a, int b) {
    mathtest::MathRequest request;

    request.set_a(a);
    request.set_b(b);

    mathtest::MathReply reply;

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

void Run() {
  std::string address("0.0.0.0:5001");
  MathTestCliImpl client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

  int response;

  int a = 5;
  int b = 10;

  response = client.sendRequest(a, b);
  std::cout << "Answer received: " << a << " * " << b << " = " << response << std::endl;
}
