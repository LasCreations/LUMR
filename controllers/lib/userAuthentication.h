#ifndef USER_AUTHENTICATION_H
#define USER_REGISTRATION_CONTROLLER_H

#include "cache.h"

void handleUserAuthentication(CLIENT *client);
std::string extractCookieValue(const std::string request);

#endif