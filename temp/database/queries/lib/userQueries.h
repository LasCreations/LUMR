#ifndef USER_QUERIES_H
#define USER_QUERIES_H

#include"../../connection/lib/DBManager.h"


bool addDataToUserTable(DATABASEMANAGER *dbMan, USER *data);

bool addDataToUserProfileTable(DATABASEMANAGER *dbMan, USER *data);

bool updateToken(DATABASEMANAGER *dbMan, USER *data, string token);

bool updateUserProfile(DATABASEMANAGER *dbMan, USER *data);

std::unordered_map<string, USER *> *getUsersCacheData(DATABASEMANAGER *dbMan);
#endif