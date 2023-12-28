#ifndef JSON_PARSER_H
#define JSON_PARSER_H


#include<iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include "../../models/user.h"
#include "../../models/connection.h"
#include "vector"

using namespace std;


PROFILE *parseProfileTokens(string JsonString);
USER *parseTokens(string JsonString);
USER *parseRegisterTokens(string JsonString);


string parseTokenFromRequest(string JsonString);


string UnparseUserDataToJSON(USER *user, bool isFriend, uint32_t followercount, uint32_t followingcount);


string createJSONObjectArray(vector<CONNECTION> followers, vector<CONNECTION> following, string request);
#endif