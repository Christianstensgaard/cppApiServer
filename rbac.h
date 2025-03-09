#pragma once

#include <string>
#include "mock_dataModel.h"



namespace REST_API{
  class RoleBasedAccessControl{
    public:
    bool checkPermission(const MOCK::User& user, const std::string& action, const std::string& resource);

  };
}