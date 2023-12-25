#ifndef JSON_PARSER_H
#define JSON_PARSER_H


#include<iostream>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include "../../models/user.h"

using namespace std;


PROFILE *parseProfileTokens(string JsonString);
USER *parseTokens(string JsonString);
string ParseUserDataToJSON(USER *user);
string parseTokenFromRequest(string JsonString);

#endif