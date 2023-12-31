#ifndef WEB_PAGES_CONTROLLER
#define WEB_PAGES_CONTROLLER

#include "../../utils/common.h"

bool handlePageRequest(char *route, int clientSocket);

void getFileURL(char *route, char *fileURL);

void getMimeType(char *file, char *mime);

void getTimeString(char *buf);


#endif