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

#endif