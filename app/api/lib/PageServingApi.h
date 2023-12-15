#ifndef PAGE_SERVING_API
#define PAGE_SERVING_API

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