#include "routeConfig.h"

namespace TCP {

    std::unordered_map<std::string, std::string> RouteConfig::sessionStore;
    std::mutex RouteConfig::sessionMutex;

    RouteConfig::RouteConfig() : nextId(0) {}

    RouteConfig::~RouteConfig() {}

    void RouteConfig::createRoute(const std::string& route, std::function<std::string(const std::string&)> callback) {
        routes.push_back({nextId++, route, callback});
    }

    std::string RouteConfig::handleRequest(const std::string& route, const std::string& body) {
        std::cout << "route: " << route << "\n";

        for (const auto& routeModel : routes) {
            if (route == routeModel.route) {
                return routeModel.callback(body);
            }
        }
        return R"({"error": "Route not found"})";
    }
}
