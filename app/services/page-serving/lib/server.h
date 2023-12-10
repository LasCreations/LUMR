#ifndef SERVER_H
#define SERVER_H

#include "get_requests.h"

#include "../models/user.h"


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

#define SIZE 1024  // buffer size
#define PORT 8089  // port number
#define BACKLOG 10 // number of pending connections queue will hold



class Server{
    private:
        int serverSocket;
        int clientSocket;
        char *request;
        // std::string dbRequest;

    public: 
        //Default Constructor
        Server();

        int StartHttpServer();

        static void handleSignal(int signal);

        // Static method to get the instance of the singleton
        static Server& getInstance();

        

};
#endif