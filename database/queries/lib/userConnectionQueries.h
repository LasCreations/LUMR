#ifndef USER_CONNECTION_QUERIES_H
#define USER_CONNECTION_QUERIES_H

#include"../../connection/lib/DBManager.h"
#include "userCache.h"
#include "../../../utils/common.h"

bool addConnectionToDatabase(DATABASEMANAGER *dbMan, CONNECTION *data);

bool updateUser1Status(bool status,  string username, DATABASEMANAGER *dbMan);

bool updateUser2Status(bool status, string username,DATABASEMANAGER *dbMan);

std::unordered_map<string, CONNECTION *> *getConnectionCacheData(DATABASEMANAGER *dbMan, USERCACHE *userCacheData);

#endif