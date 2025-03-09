#ifndef REST_SERVER_H
#define REST_SERVER_H

#include <boost/asio.hpp>
#include <thread>
#include "routeConfig.h"
#include <string>
#include "json.hpp"
#include <iostream>

namespace TCP {

    class REST_Api {
    public:
        REST_Api();  
        ~REST_Api();

        RouteConfig& config();
        bool openConnection();
        bool closeConnection();
        void startServer();
        void handleClient(boost::asio::ip::tcp::socket socket);
        static void extractHeaderAndBody(const std::string& request, std::string& header, std::string& body);

    private:
        boost::asio::io_context ioContext;
        boost::asio::ip::tcp::acceptor acceptor;
        RouteConfig* pRougeConfig;
        std::thread* pServerThread;
        std::string getContentType(const std::string& route); 
    };

}  

#endif  // REST_SERVER_H
