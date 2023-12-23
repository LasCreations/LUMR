#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H


#include "../../database/queries/lib/userQueries.h"
#include "../../middleware/cache/lib/userCache.h"

void addUser(char* request, int clientSocket, USERCACHE *userCacheData);

bool userExistsInCache(char* request, int clientSocket, USERCACHE *userCacheData);

USER *parseSignupTokens(string JsonString);


#endif