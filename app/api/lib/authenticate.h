#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H



#ifdef __cplusplus
// C++ specific code goes here
#include <iostream>
#include <string>

std::string generateRandomCookieCode(int length);
void ParseData(std::string &username, std::string &email, std::string &password, char *postData);
string ParseJSON(char *body);
void handleJSONRequests(string data, int clientSocket);
void handleSignUpRequest(char *data, int clientSocket);
#endif




#ifdef __cplusplus
extern "C" {
#endif

void handlePostRequests(char *request, char *body, char* route, int clientSocket);

#ifdef __cplusplus
}
#endif



#endif