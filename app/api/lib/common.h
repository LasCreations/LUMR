#ifndef COMMON_H
#define COMMON_H

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

#include<string>
#include<iostream>
#include<regex>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>


#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>

#include <fstream>
#include <cstring>

#include <stdbool.h>

using namespace std;

#define SIZE 1024  // buffer size
// #define PORT 8080  // port number
// #define BACKLOG 10 // number of pending connections queue will hold

#include "../../database/lib/DBConnector.h"
#include "../../database/models/user.h"


extern DBConnector *dbConn; 
extern std::string username, email, password, avatarurl, cookie; 



// /*!
//  * @function    getUserData
//  * @abstract    
//  * @discussion  
//  * @param       cookie
//  * @result      
// */
string parseHttpRequest(char *request);

string generateRandomCode(int length);

#endif