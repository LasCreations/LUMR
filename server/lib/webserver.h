#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <stdio.h>  // console input/output, perror
#include <stdlib.h> // exit
#include <string.h> // string manipulation
#include <netdb.h>  // getnameinfo

#include <arpa/inet.h>  // Include for htonl function
#include <sys/socket.h> // socket APIs
#include <netinet/in.h> // sockaddr_in
#include <unistd.h>     // open, close

#include <signal.h> // signal handling
#include <time.h>   // time
#include <errno.h>

#include <pthread.h>
#include <inttypes.h>


#define SIZE 1024  // buffer size
#define PORT 8081  // port number
#define BACKLOG 500 // number of pending connections queue will hold

int serverSocket;


#include "../../routes/lib/routes.h"
#include "../../middleware/cache/lib/userCache.h"
#include "../../middleware/cache/lib/notificationCache.h"
#include "../../middleware/cache/lib/userConnectionCache.h"
#include "../../database/connection/lib/DBManager.h"


NOTIFICATIONCACHE *cacheNotificationData;
USERCACHE *cacheUserData;
USERCONNECTIONCACHE *cacheConnectionData;
DATABASEMANAGER *dbMan;

struct Request {
    int clientSocket;
    char* request;
};

int runServer();

static void handleSignal(int signal);

void preloadCacheIntoMemory();

void *handleClientSideRequests(void *req);

void *handlePollingRequests(void *req);

#endif