#ifndef SEARCH_API_H
#define SEARCH_API_H

// C++ specific code goes here
#ifdef __cplusplus

#include "common.h"
#include "connections.h"



string parseUsernameToken(string JsonString, string user_id);

User *searchUsername(string target);

string ParseSearchDataToJSON(string username, string avatarurl, bool status);


#endif



#ifdef __cplusplus
extern "C" {
#endif

// C specific code goes here
void searchUser(char *request, int clientSocket);

#ifdef __cplusplus
}
#endif

#endif