#ifndef DEGREE_CONTROLLER_H
#define DEGREE_CONTROLLER_H

#include "cache.h"

void handleDegrees(CLIENT *client);
std::string parseDegreeRequest(std::string request);
std::string createDegreeJsonArray(std::unordered_map<std::string, DEGREE> degrees);


#endif