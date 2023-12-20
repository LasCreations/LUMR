#ifndef FOLLOWERS_API_H
#define FOLLOWERS_API_H

// C++ specific code goes here
#ifdef __cplusplus

#include "common.h"



void parseFollowRequestTokens(string JsonString);

bool addFriendshipToDatabase(); 

bool checkFriendship(string userID_1, string userID_2);

#endif



#ifdef __cplusplus
extern "C" {
#endif

// C specific code goes here
void followUser(char *request, int clientSocket);


#ifdef __cplusplus
}
#endif

#endif