/*
* @brief : 手动发布消息
* 1. 启动一个任意的 sidecar
* dapr run --app-id publish
* 2. 往 sidecar 发布消息
* dapr publish --publish-app-id publish --pubsub pubsub --topic A --data '{"orderId": "100"}'
* @brief: 自动发布消息
* 1. 启动客户端
* 1. 向 sidecar 监听的端口发送消息
*/

#include <grpcpp/grpcpp.h>
#include <httplib.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  // 与当前 app 绑定的 sidecar 的监听端口
  httplib::Client cli("0.0.0.0", 8090);

  cli.Post("/v1.0/publish/pubsub/A","[{\"orderId\": \"1\"}]", "application/json");

  return 0;
}
