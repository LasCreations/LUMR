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


#define SIZE 1024  // buffer size
#define PORT 8080  // port number
#define BACKLOG 10 // number of pending connections queue will hold


#include "../../api/lib/pageserving.h"
#include "../../api/lib/authenticate.h"

int runServer();


static void handleSignal(int signal);

#endif