#ifndef CONNECTION_CONTROLLER_H
#define CONNECTION_CONTROLLER_H

#include "../../database/queries/lib/userConnectionQueries.h"
#include "../../middleware/cache/lib/userCache.h"
#include "../../jsonparsing/lib/jsonParser.h"

void addConnection(char* request, int clientSocket, DATABASEMANAGER *dbMan, USERCACHE *userCacheData);

#endif