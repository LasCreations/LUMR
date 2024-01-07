#ifndef USER_AUTHENTICATION_H
#define USER_REGISTRATION_CONTROLLER_H

#include "cache.h"

void handleUserAuthentication(CLIENT *client);
void handleUserLoginAuthentication(CLIENT *client);
std::string extractCookieValue(const std::string request);
std::string createUserJson(USER user, USERINSTITUTION userInst);
void parseLoginRequest(std::string request, std::string &username, std::string &password);


#endif