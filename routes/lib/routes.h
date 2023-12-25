#ifndef ROUTE_H
#define ROUTE_H

#include "../../utils/common.h"

#include "../../controllers/lib/webpagesController.h"
#include "../../controllers/lib/userController.h"
#include "../../controllers/lib/connectionController.h"

#include "../../middleware/cache/lib/userCache.h"

extern char method[10], route[100];


void apiRoute(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

#endif