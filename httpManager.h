#pragma once
#include <string>
namespace webTools{
  class HttpManager{
    public:
    HttpManager();
    ~HttpManager();


    std::string createHeader(std::string contentBody, std::string contentType);
    std::string getRoute();


    private:
    std::string httpContent;
  };
}