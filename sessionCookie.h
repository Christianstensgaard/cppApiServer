#pragma once
#include <string>
#include <iostream>
namespace webTools{
  class SessionCookie{

    public:
    void setSessionCookie(std::string& response, const std::string& sessionId);
    bool isSessionValid(const std::string& sessionId);
    std::string generateSessionId();


    private:
    



  };

}