#ifndef CONNECTION_CONTROLLER_H
#define CONNECTION_CONTROLLER_H

#include "../../database/queries/lib/userConnectionQueries.h"

#include "../../jsonparsing/lib/jsonParser.h"

#include "../../middleware/cache/lib/userCache.h"
#include "../../middleware/cache/lib/userConnectionCache.h"

void addConnection(char* request, int clientSocket, DATABASEMANAGER *dbMan, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

#endif