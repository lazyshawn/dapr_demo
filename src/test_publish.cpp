#include <grpcpp/grpcpp.h>
#include <httplib.h>
#include <iostream>
#include <string>

// 手动发布消息:
// 1. 启动一个任意的 sidecar
// dapr run --app-id publish --dapr-http-port 8090
// 2. 往 sidecar 发布消息
// dapr publish --publish-app-id publish --pubsub pubsub --topic A --data '{"orderId": "100"}'

int main(int argc, char** argv) {
  // 当前 app 的监听端口
  httplib::Server svr;

  svr.Post("/publish/pubsub/A", [](const httplib::Request &, httplib::Response &res) {
    std::string topicJson = "[{\"orderId\": \"1\"}]";
    res.set_content("ss", "application/json");
  });

  // 启动服务端
  svr.listen("0.0.0.0", 8090);

  return 0;
}
