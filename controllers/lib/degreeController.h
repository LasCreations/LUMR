#ifndef DEGREE_CONTROLLER_H
#define DEGREE_CONTROLLER_H

#include "cache.h"

void handleDegrees(CLIENT *client);
std::string parseDegreeRequest(std::string request);
std::string createDegreeJsonArray(std::vector<DEGREE> *degrees);
Json::Value createDegreeJsonObject(std::string name);

#endif