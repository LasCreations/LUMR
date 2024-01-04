#ifndef SERVER_H
#define SERVER_H

#include "route.h"

#define PORT 8081  // port number
#define BACKLOG 500 //number of pending connections queue will hold

/*!
 * @function    confiureServer
 * @abstract    set up the server and start listening to
 *              incoming http requests
 * @result      1 or 0
*/
int confiureServer();

/*!
 * @function    handleSignal
 * @abstract    when (Ctrl+C) is clicked an interrupt signal
 *              is sent and the program ends and the server is shut
 *              down.
 * @param       int    signal
 * @result      nothing
*/
void handleSignal(int signal);

/*!
 * @function    read_from_client
 * @abstract    read bytes from client request
 * @param       int    clientSocket
 * @param       char* request
 * @result      nothing
*/
int readRequest(int clientSocket);

/*!
 * @function    handleThreadAlloctions
 * @abstract    handle the allocation of threads based off 
 *              user requests
 * @param       int    clientSocket
 * @param       char* request
 * @param       char* method
 * @param       char* route
 * @result      nothing
*/
void handleThreadAlloctions(int clientSocket, char* request, char *method, char *route);

/*!
 * @function    joinedThread
 * @abstract    
 *              to client
 * @param       void*   client
 * @result      NULL
*/
void *joinedThread(void *clientThread);

/*!
 * @function    detachedThreads
 * @abstract    
 *              resources
 * @param       void*   client
 * @result      NULL
*/
void *detachedThreads(void *clientThread);

/*!
 * @function    printClientInformation
 * @abstract    prints the information in the struct
 * @param       CLIENT *client
 * @result      
*/
void printClientInformation(CLIENT *client);
#endif