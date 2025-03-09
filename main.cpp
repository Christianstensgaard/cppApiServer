#include "restServer.h"
#include "mock_dataModel.h"
#include "rbac.h"
#include "swaggerUiHandler.h"
#include "json.hpp"

int main() {
    TCP::REST_Api apiServer;
    REST_API::RoleBasedAccessControl rbac;

  apiServer.config().createRoute("/articles", [&rbac](const std::string& body) {
      MOCK::User user  = MOCK::getUserFromRequest();

      if (rbac.checkPermission(user, "read", "article")) {
          return R"([{"article_id": 1, "title": "Article 1", "content": "Content"}])";
      } else {
          return R"({"error": "Forbidden"})";
      }
  });

  apiServer.config().createRoute("/create_article", [&rbac](const std::string& body) {
    std::cout << "Create new Article" << "\n";
    return "hello";
  });

  apiServer.config().createRoute("/edit_article", [&rbac](const std::string& body) {
      MOCK::User user  = MOCK::getUserFromRequest();

      if (rbac.checkPermission(user, "edit", "article")) {
          return R"({"message": "Article edited"})";
      } else {
          return R"({"error": "Forbidden"})";
      }
  });

  apiServer.config().createRoute("/login", [](const std::string& request) {
    std::string header, body;
    TCP::REST_Api::extractHeaderAndBody(request, header, body);

    try {
      auto json_data = nlohmann::json::parse(body);

      std::string username = json_data.value("username", "");
      std::string password = json_data.value("password", "");

      if (username.empty() || password.empty()) {
          return std::string(R"({"error": "Missing username or password"})");
      }

      MOCK::User user = MOCK::getUserByUsername(username);

      if (user.username.empty() || user.password_hash != password) {
          return std::string(R"({"error": "Invalid username or password"})");
      }

      return std::string("{\"message\": \"Login successful\", \"session_id\": \"") + "sessionId" + "\"}";

    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return std::string(R"({"error": "Invalid JSON format"})");
    }
  });

  apiServer.config().createRoute("/sessions", [](const std::string& request) {
    return "Hello this part is removed!";
  });



  /// SWAGGER
  apiServer.config().createRoute("/", [](const std::string& body) {
    return Swagger::serveSwaggerUi();
  });
  apiServer.config().createRoute("/swagger.json", [](const std::string& body) {
    return Swagger::serveSwaggerJson();
  });
  apiServer.config().createRoute("/swagger-ui", [](const std::string& body) {
    return Swagger::serveSwaggerUi();
  });
  apiServer.config().createRoute("/swagger-ui/swagger-ui-bundle.js", [](const std::string& body) {
    return Swagger::serveSwaggerJs();
  });
  apiServer.config().createRoute("/swagger-ui/swagger-ui.css", [](const std::string& body) {
    return Swagger::serveSwaggerCss();
  });
  apiServer.config().createRoute("/swagger-ui/swagger-ui-theme.css", [](const std::string& body) {
    return Swagger::serveSwaggerCssTheme();
  });

  std::cout << "Application Running" << std::endl;

  while (true) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}
