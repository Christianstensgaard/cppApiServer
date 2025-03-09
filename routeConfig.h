#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <unordered_map>
#include "mock_dataModel.h"
#include <mutex>
#include "json.hpp"
#include <cstdlib>  

namespace TCP {

  struct routeModel {
    unsigned int id;
    std::string route;
    std::function<std::string(const std::string&)> callback; 
  };

  class RouteConfig {
    public:
      RouteConfig();
      ~RouteConfig();

      void createRoute(const std::string& route, std::function<std::string(const std::string&)> callback);
      std::string handleRequest(const std::string& route, const std::string& requestBody);
      static std::string extractFieldFromJson(const std::string& json, const std::string& field);

    private:
      std::vector<routeModel> routes;
      unsigned int nextId = 1;

      static std::unordered_map<std::string, std::string> sessionStore;
      static std::mutex sessionMutex;
    };
}
