#ifndef PAGE_RENDERING_H
#define PAGE_RENDERING_H

#include "common.h"

// void handlePageRequest(char *route, int clientSocket);
void handlePageRequest(CLIENT *client);

void getFileURL(char *route, char *fileURL);

void getMimeType(char *file, char *mime);

void getTimeString(char *buf);

#endif