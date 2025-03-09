#include "mock_dataModel.h"

namespace MOCK {
  User getUserFromRequest() {
      return User();  
  }
  // Mock database of users
  static std::vector<User> users = {
    {1, "editor", "hashed", "editor"},
    {2, "journalist", "hashed", "journalist"},
    {3, "subscriber", "hashed", "subscriber"}
  };

  User getUserByUsername(const std::string& username) {
    for (const auto& user : users) {
        if (user.username == username) {
            return user;
        }
    }
    return User();
  }
}