#ifndef INSTITUTIONS_CONTROLLER_H
#define INSTITUTIONS_CONTROLLER_H

#include "cache.h"

void handleInstitutions(CLIENT *client);
std::string createInstitutionJsonArray(std::unordered_map<std::string, INSTITUTION>& institutions);
Json::Value createInstitutionJsonObject(std::string name);


#endif