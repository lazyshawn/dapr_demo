#include <grpcpp/grpcpp.h>
#include <httplib.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  // 当前 app 的监听端口
  httplib::Server svr;

  // 监听 /dapr/subscribe 路由，在请求时以 JSON 数组的形式返回要订阅的主题名称
  svr.Get("/dapr/subscribe", [](const httplib::Request &, httplib::Response &res) {
    std::string topicJson = "[{\"pubsubname\":\"pubsub\", \"topic\": \"A\", \"route\": \"A\"}]";
    res.set_content(topicJson, "application/json");
  });

  // 当发布方向订阅的主题发布内容时，边车会通过 POST 请求向你发送事件：
  svr.Post("/A", [](const httplib::Request &req, httplib::Response &res) {
    std::cout << "get a message: " << req.body << std::endl;
  });

  // 启动服务端
  svr.listen("0.0.0.0", 8088);

  return 0;
}
