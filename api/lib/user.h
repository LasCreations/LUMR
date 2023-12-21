#ifndef USER_API_H
#define USER_API_H

/*
/api/users?{userId}? (GET, PUT, DELETE) Get, update, or delete a specific user.
/api/users/me (GET, PUT, DELETE) Get, update, or delete a specific user.
*/

// C++ specific code goes here
#ifdef __cplusplus

#include "../../include/common.h"
#include "../../cache/lib/user_data.h"



void parseCookieToken(string JsonString);

string ParseUserDataToJSON(User *user);

#endif



#ifdef __cplusplus
extern "C" {
#endif

// C specific code goes here

void findUser(char *request, int clientSocket, UserDataCache *cacheData);



#ifdef __cplusplus
}
#endif

#endif