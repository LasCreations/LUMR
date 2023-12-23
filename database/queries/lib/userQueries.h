#ifndef USER_QUERIES_H
#define USER_QUERIES_H

#include"../../connection/lib/DBManager.h"


bool addDataToUserTable(USER *data);

bool addDataToUserProfileTable(USER *data);

std::unordered_map<string, USER *> *getUsersCacheData();
#endif