#ifndef USER_REGISTRATION_CONTROLLER_H
#define USER_REGISTRATION_CONTROLLER_H

#include "cache.h"

struct USERINSTITUTION{
    std::vector<std::string> degrees;
    std::vector<std::string> courses;
    std::string institution;
    std::string username;
};

void handleUserRegistration(CLIENT *client);
USER parseUserDetails(std::string jsonData);
USERINSTITUTION parseUserInstitutionDetails(std::string jsonData);
void addRelations(USERINSTITUTION userInstData, USER user);

#endif