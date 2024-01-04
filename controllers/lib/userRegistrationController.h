#ifndef USER_REGISTRATION_CONTROLLER_H
#define USER_REGISTRATION_CONTROLLER_H

#include "cache.h"

void handleUserRegistration(CLIENT *client);
USER parseUserRegistrationRequest(std::string jsonData);

#endif