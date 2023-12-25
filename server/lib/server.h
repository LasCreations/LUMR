#ifndef SERVER_H
#define SERVER_H

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
#define BACKLOG 10 // number of pending connections queue will hold

int serverSocket;


#include "../../routes/lib/routes.h"
#include "../../middleware/cache/lib/userCache.h"
#include "../../database/connection/lib/DBManager.h"


USERCACHE *cacheUserData;
DATABASEMANAGER *dbMan;

int runServer();

static void handleSignal(int signal);

void *handleRequests(void *pClientSocket);

#endif