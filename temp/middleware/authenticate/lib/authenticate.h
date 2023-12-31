#ifndef AUTHENTICATE_LOGIN_H
#define AUTHENTICATE_LOGIN_H

#include "../../jsonparsing/lib/jsonParser.h"
#include "../../middleware/cache/lib/userCache.h"
#include "../../middleware/cache/lib/userConnectionCache.h"

void checkUserCredentials(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

bool updateUserToken(USER *user, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

bool verifyUserToken(char *request, USERCACHE *userCacheData, int clientSocket);


#endif