#ifndef PAGE_RENDERING_H
#define PAGE_RENDERING_H

#include "common.h"

bool handlePageRequest(char *route, int clientSocket);

void getFileURL(char *route, char *fileURL);

void getMimeType(char *file, char *mime);

void getTimeString(char *buf);


#endif