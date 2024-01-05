#ifndef COMMON_H
#define COMMON_H

#include "headers.h"

#define SIZE 4096  // buffer size

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


/*!
 * @function    generateRandomCode
 * @abstract    create a code with a given length
 * @param       int    lenght
 * @result      returns a string
*/
std::string generateRandomCode(int length);

/*!
 * @function    getCurrentTime
 * @abstract    converts the current time on the server
 *              to a string
 * @param       null
 * @result      returns a string
*/
std::string getCurrentTime();
#endif