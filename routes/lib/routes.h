#ifndef ROUTE_H
#define ROUTE_H

//Common functions and libraries
#include "../../utils/common.h"

//Controllers
#include "../../controllers/lib/webpagesController.h"
#include "../../controllers/lib/userController.h"
#include "../../controllers/lib/connectionController.h"

//Caching
#include "../../middleware/cache/lib/userCache.h"
#include "../../middleware/cache/lib/userConnectionCache.h"

extern char method[10], route[100];


void apiRoute(char *request, int clientSocket, USERCACHE *userCacheData,
                DATABASEMANAGER *dbMan, USERCONNECTIONCACHE *cacheConnectionData);

#endif