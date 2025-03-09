#include "rbac.h"
//Should be changed to COR at some point, but doing this so simplicity atm. 
bool REST_API::RoleBasedAccessControl::checkPermission(const MOCK::User &user, const std::string &action, const std::string &resource)
{
  if (user.role == "editor") {
    return true;
  } else if (user.role == "journalist" && resource == "article") {
      return action == "create" || action == "edit";
  } else if (user.role == "subscriber" && resource == "comment") {
      return action == "create";
  } else if (user.role == "guest" && resource == "article") {
      return action == "read";
  }
  return false;
}