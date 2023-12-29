#ifndef JSON_PARSER_H
#define JSON_PARSER_H


#include<iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include "../../models/user.h"
#include "../../middleware/cache/lib/userConnectionCache.h"
#include "../../middleware/cache/lib/notificationCache.h"
#include "vector"

using namespace std;


PROFILE *parseProfileTokens(string JsonString);

USER *parseTokens(string JsonString);

USER *parseRegisterTokens(string JsonString);

string parseTokenFromRequest(string JsonString);

string UnparseUserDataToJSON(USER *user, bool isFriend, uint32_t followercount, uint32_t followingcount);

string createJSONObjectArray(vector<CONNECTION> users, string username, USERCONNECTIONCACHE *cacheConnectionData);

Json::Value createJSONObjectFollowView(string username, string avatarurl, bool status);

string createNotificationObjectArray(vector<NOTIFICATION> notification, 
                                        USERCONNECTIONCACHE *cacheConnectionData,
                                        USERCACHE *userCache);

Json::Value createJSONObjectNotification(NOTIFICATION notification, string avatarurl, bool status);
#endif