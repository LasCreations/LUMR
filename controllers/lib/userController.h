#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H


#include "../../database/queries/lib/userQueries.h"
#include "../../middleware/cache/lib/userCache.h"

void addUser(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

void updateUserProfile(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

bool userExistsInCache(char* request, int clientSocket, USERCACHE *userCacheData);

void checkUserCredentials(char* request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

void userDataDashBoard(char* request, int clientSocket, USERCACHE *userCacheData);

bool updateUserToken(USER* user, USERCACHE *userCacheData, DATABASEMANAGER *dbMan);

string ParseUserDataToJSON(USER *user);

USER *parseTokens(string JsonString);

PROFILE *parseProfileTokens(string JsonString);


#endif