#include "restServer.h"

namespace TCP {
  REST_Api::REST_Api()
      : acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8080)) {
      pRougeConfig = new RouteConfig();
      pServerThread = new std::thread(&REST_Api::startServer, this);
  }
  REST_Api::~REST_Api() {
    delete pRougeConfig;
    delete pServerThread;
  }
  RouteConfig& REST_Api::config() {
    return *pRougeConfig;
  }
  bool REST_Api::openConnection() {
    return true;
  }
  bool REST_Api::closeConnection() {
    ioContext.stop();
    return true;
  }
  std::string extractRouteFromRequest(const std::string& request) {
      size_t pos = request.find(" ");
      if (pos == std::string::npos) return "";

      size_t endPos = request.find(" ", pos + 1);
      if (endPos == std::string::npos) return "";

      return request.substr(pos + 1, endPos - pos - 1);
  }
  void REST_Api::startServer() {
      std::cout << "Server started on port 8080...\n";
      while (true) {
          boost::asio::ip::tcp::socket socket(ioContext);
          acceptor.accept(socket);
          std::thread(&REST_Api::handleClient, this, std::move(socket)).detach();
      }
  }
  std::string REST_Api::getContentType(const std::string& route) {
      if (route == "/swagger.json" || route == "/swagger.yaml") {
          return "application/json";
      } else if (route == "/swagger-ui" || route == "/swagger-ui/swagger-ui-bundle.js" ||
                  route == "/swagger-ui/swagger-ui.css" || route == "/swagger-ui/swagger-ui-theme.css") {
          if (route.find(".js") != std::string::npos) {
              return "application/javascript";
          } else if (route.find(".css") != std::string::npos) {
              return "text/css";
          } else {
              return "text/html";
          }
      } else {
          return "text/html";
      }
  }
  void REST_Api::handleClient(boost::asio::ip::tcp::socket socket) {
      try {
          char buffer[1024];
          boost::system::error_code error;
          size_t length = socket.read_some(boost::asio::buffer(buffer), error);

          if (error) {
              std::cerr << "Read error: " << error.message() << "\n";
              return;
          }

          std::string request(buffer, length);
          std::string route = extractRouteFromRequest(request);

          std::string responseBody = pRougeConfig->handleRequest(route, request);

          //- This is moved to HttpManager
          std::string httpResponse =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: " + getContentType(route) + "\r\n"
            "Content-Length: " + std::to_string(responseBody.size()) + "\r\n"
            "\r\n" +
            responseBody;

          boost::asio::write(socket, boost::asio::buffer(httpResponse), error);
      } catch (std::exception& e) {
          std::cerr << "Exception: " << e.what() << "\n";
      }
  }
  std::string extractFieldFromJson(const std::string& json, const std::string& field) {
    try {

      if (json.empty()) {
        return R"({"error": "Empty request body"})";
      }


        // Parse the string as JSON
        auto j = nlohmann::json::parse(json);

        // Check if the field exists
        if (j.contains(field)) {
            return j[field].get<std::string>();
        } else {
            return "";  // Return an empty string if the field does not exist
        }
    } catch (const std::exception& e) {
        // Handle parsing errors (e.g., malformed JSON)
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return "";
    }
  }
  void REST_Api::extractHeaderAndBody(const std::string& request, std::string& header, std::string& body) {
    size_t body_start_pos = request.find("\r\n\r\n");

    if (body_start_pos != std::string::npos) {
        header = request.substr(0, body_start_pos);  
        body = request.substr(body_start_pos + 4);  
    }
    else {
        header = request;
        body = "";
    }
    std::cout << "Header: \n" << header << "\n";
    std::cout << "Body: \n" << body << "\n";
  }
}
