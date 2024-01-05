#ifndef USER_AUTHENTICATION_H
#define USER_REGISTRATION_CONTROLLER_H

#include "cache.h"

void handleUserAuthentication(CLIENT *client);
std::string extractCookieValue(const std::string request);
// USER parseUserDetails(std::string jsonData);
// USERINSTITUTION parseUserInstitutionDetails(std::string jsonData);
// void addRelations(USERINSTITUTION userInstData, USER user);

#endif