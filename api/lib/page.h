#ifndef PAGE_SERVING_API_H
#define PAGE_SERVING_API_H

#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

bool handlePageRequest(char *route, int clientSocket);

#ifdef __cplusplus
}
#endif



void getFileURL(char *route, char *fileURL);

void getMimeType(char *file, char *mime);

void getTimeString(char *buf);

#endif