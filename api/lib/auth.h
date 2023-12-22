#ifndef AUTH_API_H
#define AUTH_API_H


/*
/api/auth/ (POST) -> [checks if user is authenticated] [return bool]
/api/auth/login (POST) -> [sends username and password to log in user] [sends a 200 response to client if successful]
/api/auth/logout (POST) -> [changes user status to false]
/api/auth/register (POST) -> [adds User to database] [sends a 200 response to client if successful]
*/




// C++ specific code goes here
#ifdef __cplusplus

#include "../../include/common.h"
#include "../../cache/lib/user_data.h"


User *parseJSONTokens(string JsonString);

bool addUserToDatabase(User *data);

void parseLoginTokens(string JsonString);


bool updateUserCookieDB(User *data);

#endif



#ifdef __cplusplus
extern "C" {
#endif

// C specific code goes here
void registerUser(char *request, int clientSocket, UserDataCache *cacheData);

void loginUser(char *request, int clientSocket, UserDataCache *cacheData);

bool isAuth(char *request, int clientSocket);

#ifdef __cplusplus
}
#endif




#endif