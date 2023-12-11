#ifndef POST_REQUEST_H
#define POST_REQUEST_H

#include<regex>
#include "server.h"

// Forward declaration of Server class
class Server;

void handlePostRequests(char *method, char *data, int clientSocket, Server& serverInstance);

void handleJSONRequests(char *method, const char *data, int clientSocket, Server& serverInstance);

void ParseData(std::string &username,std::string  &email,std::string  &password, char *postData);

#endif