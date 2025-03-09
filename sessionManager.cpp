#include "SessionManager.h"

namespace webTools { 

  std::unordered_map<std::string, std::string> SessionManager::sessionStore;
  std::mutex SessionManager::sessionMutex;

  std::string SessionManager::generateSessionId() {
      return "session-" + std::to_string(std::rand());
  }

  void SessionManager::storeSession(const std::string& sessionId, const std::string& username) {
      std::lock_guard<std::mutex> lock(sessionMutex);
      sessionStore[sessionId] = username;
  }

  bool SessionManager::isSessionValid(const std::string& sessionId) {
      std::lock_guard<std::mutex> lock(sessionMutex);
      return sessionStore.find(sessionId) != sessionStore.end();
  }

  MOCK::User SessionManager::getUserFromSession(const std::string& sessionId) {
      std::lock_guard<std::mutex> lock(sessionMutex);
      if (!isSessionValid(sessionId)) {
          throw std::runtime_error("Invalid session");
      }
      std::string username = sessionStore[sessionId];
      return MOCK::getUserByUsername(username);
  }

  std::string SessionManager::extractSessionIdFromRequest(const std::string& request) {
      std::cout << "requestBody: "  << request << "\n";
      return "";
  }

  std::vector<std::string> SessionManager::getAllActiveSessions() {
      std::lock_guard<std::mutex> lock(sessionMutex);
      std::vector<std::string> activeSessions;
      for (const auto& session : sessionStore) {
          activeSessions.push_back(session.first);
      }
      return activeSessions;
  }
}
