#ifndef COMMON_H
#define COMMON_H

#include "headers.h"

#define SIZE 1024  // buffer size

//Creating a structure of client information to pass to threads
struct CLIENT {
    int socket;
    char* request;
    char* method;
    char* route;
};

/*!
 * @function    parseHttpRequest
 * @abstract    Removes the json data from a request
 * @param       char*   request
 * @result      returns a string
*/
std::string parseHttpRequest(char *request);

#endif