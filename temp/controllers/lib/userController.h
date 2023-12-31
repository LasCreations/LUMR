#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H


#include "../../database/queries/lib/userQueries.h"

#include "../../jsonparsing/lib/jsonParser.h"

#include "../../middleware/cache/lib/userCache.h"
#include "../../middleware/cache/lib/notificationCache.h"
#include "../../middleware/cache/lib/userConnectionCache.h"



void addUser(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

void userDataDashBoard(char* request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

void searchUser(char* request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

void getFollowers(char* request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

void getFollowing(char* request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData);

void getNotification(   char* request, int clientSocket,
                        USERCACHE *userCacheData, 
                        USERCONNECTIONCACHE *cacheConnectionData, 
                        NOTIFICATIONCACHE *cacheNotificationData,
                        DATABASEMANAGER *dbMan );
#endif