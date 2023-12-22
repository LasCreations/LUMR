#ifndef SEARCH_API_H
#define SEARCH_API_H

// C++ specific code goes here
#ifdef __cplusplus

#include "../../include/common.h"




void parseUsernameToken(string JsonString);

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