#ifndef GET_REQUEST_H
#define GET_REQUEST_H


#include "server.h"

void handleGetRequests(char *route, int clientSocket);

void getFileURL(char *route, char *fileURL);

void getMimeType(char *file, char *mime);

void getTimeString(char *buf);

#endif