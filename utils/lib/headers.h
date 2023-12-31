#ifndef HEADERS_H
#define HEADERS_H

//C++ Header
#include <iostream>
#include <string>
#include <regex>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <fstream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <ctime>

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
#include <errno.h>  //errors

#include <pthread.h>  //multithreading
#include <stdint.h> //unsigned integers
#include <stdbool.h> // boolean type and values

//JSON PARSER
#include <jsoncpp/json/value.h> 
#include <jsoncpp/json/json.h>

//SQL Connector
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#endif