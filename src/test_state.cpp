#include <grpcpp/grpcpp.h>
#include <httplib.h>
#include <iostream>
#include <string>

int fun(int a, int b) {
  return 10*a + b;
}

int main(int argc, char** argv) {
  // HTTP server
  httplib::Server svr;
  // 连接到 sidecar 监听的 http 端口
  httplib::Client cli("localhost", 8089);

  svr.Get("/greeting", [](const httplib::Request &, httplib::Response &res) {
    // JSON 字符串
    const std::string jsonStr = "[{\"key\": \"mystate\", \"value\": \"1\"}]";

    // 连接到 sidecar 监听的 http 端口
    httplib::Client cli("localhost", 8089);

    auto stateRes = cli.Get("/v1.0/state/statestore/mystate");

    std::string mystate = stateRes->body;
    mystate.erase(std::remove( mystate.begin(), mystate.end(), '\"' ),mystate.end());
    int count = stoi(mystate) + 1;

    std::cout << "count = " << count << std::endl;

    std::string postData = "[{\"key\": \"mystate\", \"value\": \"" + std::to_string(count) + "\"}]";
    std::cout << postData.c_str() << std::endl;

    cli.Post("/v1.0/state/statestore", postData.c_str(), "application/json");

    // 处理响应
    std::string resData = "I have greeting you " + std::to_string(count-1) + " times.";
    res.set_content(resData.c_str(), "text/plain");
  });

  svr.listen("0.0.0.0", 8088);

  return 0;
}
