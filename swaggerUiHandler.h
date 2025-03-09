#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/address.hpp>
#include <fstream>
#include <string>
#include <iostream>

namespace http = boost::beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace Swagger {

    std::string serveSwaggerJson() {
      std::ifstream swaggerFile("swagger-ui/swagger.yaml"); 
      std::string swaggerJson((std::istreambuf_iterator<char>(swaggerFile)),
                                std::istreambuf_iterator<char>());


      std::cout << "Swagger Json" << swaggerJson;
      return swaggerJson;
    }

    std::string serveSwaggerUi() {
      std::ifstream htmlFile("swagger-ui/index.html");
      std::string htmlContent((std::istreambuf_iterator<char>(htmlFile)),
                                std::istreambuf_iterator<char>());
      return htmlContent;
    }

    std::string serveSwaggerJs() {
      std::ifstream jsFile("swagger-ui/swagger-ui-bundle.js");
      std::string jsContent((std::istreambuf_iterator<char>(jsFile)),
                            std::istreambuf_iterator<char>());
      return jsContent;
    }

    // Function to serve Swagger UI CSS file
    std::string serveSwaggerCss() {
      std::ifstream cssFile("swagger-ui/swagger-ui.css");  // Path to the CSS asset
      std::string cssContent((std::istreambuf_iterator<char>(cssFile)),
                              std::istreambuf_iterator<char>());
      return cssContent;
    }

    // Function to serve Swagger UI CSS theme file (optional)
    std::string serveSwaggerCssTheme() {
      std::ifstream themeCssFile("swagger-ui/swagger-ui-theme.css");  // Path to the theme CSS asset
      std::string themeCssContent((std::istreambuf_iterator<char>(themeCssFile)),
                                    std::istreambuf_iterator<char>());
      return themeCssContent;
    }

    // Function to register all routes related to Swagger UI and JSON specification
    void registerSwaggerRoutes(tcp::socket& socket, const std::string& route) {
      if (route == "swagger.json") {
          std::string response = serveSwaggerJson();
          http::response<http::string_body> res{ http::status::ok, 11 };
          res.set(http::field::content_type, "application/json");
          res.body() = response;
          res.prepare_payload();
          http::write(socket, res);
      } else if (route == "/swagger-ui") {
          std::string response = serveSwaggerUi();
          http::response<http::string_body> res{ http::status::ok, 11 };
          res.set(http::field::content_type, "text/html");
          res.body() = response;
          res.prepare_payload();
          http::write(socket, res);
      } else if (route == "/swagger-ui/swagger-ui-bundle.js") {
          std::string response = serveSwaggerJs();
          http::response<http::string_body> res{ http::status::ok, 11 };
          res.set(http::field::content_type, "application/javascript");
          res.body() = response;
          res.prepare_payload();
          http::write(socket, res);
      } else if (route == "/swagger-ui/swagger-ui.css") {
          std::string response = serveSwaggerCss();
          http::response<http::string_body> res{ http::status::ok, 11 };
          res.set(http::field::content_type, "text/css");
          res.body() = response;
          res.prepare_payload();
          http::write(socket, res);
      } else if (route == "/swagger-ui/swagger-ui-theme.css") {
          std::string response = serveSwaggerCssTheme();
          http::response<http::string_body> res{ http::status::ok, 11 };
          res.set(http::field::content_type, "text/css");
          res.body() = response;
          res.prepare_payload();
          http::write(socket, res);
      }
    }
}
