#ifndef USER_CONNECTION_QUERIES_H
#define USER_CONNECTION_QUERIES_H

#include"../../connection/lib/DBManager.h"
#include "userCache.h"
#include "../../../utils/common.h"

bool addConnectionToDatabase(DATABASEMANAGER *dbMan, CONNECTION *data);

std::unordered_map<string, CONNECTION *> *getConnectionCacheData(DATABASEMANAGER *dbMan, USERCACHE *userCacheData);

#endif