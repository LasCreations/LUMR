#ifndef USER_API_H
#define USER_API_H

/*
/api/users?{userId}? (GET, PUT, DELETE) Get, update, or delete a specific user.
/api/users/me (GET, PUT, DELETE) Get, update, or delete a specific user.
*/

// C++ specific code goes here
#ifdef __cplusplus

#include "common.h"

void parseCookieToken(string JsonString);

User *getUserData(string cookie);

string ParseUserDataToJSON(string username, string password, string email, string avatarurl);

#endif



#ifdef __cplusplus
extern "C" {
#endif

// C specific code goes here

void findUser(char *request, int clientSocket);



#ifdef __cplusplus
}
#endif

#endif