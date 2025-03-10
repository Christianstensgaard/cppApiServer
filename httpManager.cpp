#include "httpManager.h"

std::string webTools::HttpManager::createHeader(std::string contentBody, std::string contentType)
{
  return
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: " + contentType + "\r\n"
  "Content-Length: " + std::to_string(contentBody.size()) + "\r\n"
  "\r\n" +
  contentBody;
}