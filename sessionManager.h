#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include "mock_dataModel.h"
#include <cstdlib>
#include <iostream>

namespace webTools {
  class SessionManager {
    public:
    std::string generateSessionId();
    void storeSession(const std::string& sessionId, const std::string& username);
    bool isSessionValid(const std::string& sessionId);
    MOCK::User getUserFromSession(const std::string& sessionId);
    std::string extractSessionIdFromRequest(const std::string& request);
    std::vector<std::string> getAllActiveSessions();

    private:
    static std::unordered_map<std::string, std::string> sessionStore;
    static std::mutex sessionMutex;
  };

}
