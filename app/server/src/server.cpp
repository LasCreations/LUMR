#include "../lib/server.h"

// Initialize the static instance to null
Server& Server::getInstance() {
    static Server instance;  // Create the instance if it doesn't exist
    return instance;
}

Server::Server(){}

int Server::StartHttpServer(){
    // register signal handler
    signal(SIGINT, handleSignal);

    // server internet socket address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;  // IPv4
    serverAddress.sin_port = htons(PORT); // port number in network byte order (host-to-network short)
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

    // socket of type IPv4 using TCP protocol
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // reuse address and port
    // setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    int option = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0) {
        perror("Error setting socket options");
        return 1;
    }

    // bind socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Error: The server is not bound to the address.\n");
        return 1;
    }

    // listen for connections
    if (listen(serverSocket, BACKLOG) < 0)
    {
        printf("Error: The server is not listening.\n");
        return 1;
    }

    // get server address information
    char hostBuffer[NI_MAXHOST], serviceBuffer[NI_MAXSERV];
    int error = getnameinfo((struct sockaddr *)&serverAddress, sizeof(serverAddress), hostBuffer,
                          sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), 0);

    if (error != 0){
        printf("Error: %s\n", gai_strerror(error));
        return 1;
    }

    printf("\nServer is listening on http://%s:%s/\n\n", hostBuffer, serviceBuffer);

    while (1){
        // buffer to store data (request)
        request = (char *)malloc(SIZE * sizeof(char));
        char method[10], route[100];
        
        // accept connection and read data
        clientSocket = accept(serverSocket, NULL, NULL);

        ssize_t bytesRead = read(clientSocket, request, SIZE);
        if (bytesRead < 0) {
            perror("Error reading from client socket");
            close(clientSocket);
            return 1;  // or return 1; depending on your application logic
        }

        char *body = strstr(request, "\r\n\r\n");
        if (body != NULL) {
            // Null-terminate the headers part
            *body = '\0';
            body += 4; // Move to the start of the body
        }

         // parse HTTP request
        sscanf(request, "%s %s", method, route);
        printf("%s %s", method, route);

        // only support GET method
        if (strcmp(method, "GET") == 0){
            //Restricted area for unauthenticated users
            if(strcmp(route, "/dashboard.html") == 0 || strcmp(route, "/static/styles/dashboard.css") == 0 ){
                //if user doesnt have a cookie for this website
                if(strstr(request, "Cookie:") != nullptr){
                    sendToService(request,"192.168.92.20",8089);
                }else{
                    const char response[] = "HTTP/1.1 401 Unauthorized\r\n"
                                        "Content-Type: text/html\r\n"
                                        "\r\n"
                                        "<html>"
                                        "<head><title>401 Unauthorized</title></head>"
                                        "<body>"
                                        "<h1>401 Unauthorized</h1>"
                                        "<p>You are not authenticated please login or signup.</p>"
                                        "</body>"
                                        "</html>";
                    send(clientSocket, response, sizeof(response), 0);
                }
            }else{
                sendToService(request,"192.168.92.20",8089);
            }
        }else if (strcmp(method, "POST") == 0){
            if(strcmp(route, "/submit") == 0){
                char Requeststream[100]; 
                strcpy(Requeststream, route);
                // Use strncat to concatenate with a size check
                strncat(Requeststream, " ", sizeof(Requeststream) - strlen(Requeststream) - 1);
                strncat(Requeststream, body, sizeof(Requeststream) - strlen(Requeststream) - 1);
                
                sendToService(Requeststream, "192.168.92.22", 8081);
            }
            //handlePostRequests(headers, body, route, clientSocket, *this);
        }else{
            const char response[] = "HTTP/1.1 400 Bad Request\r\n\n";
            send(clientSocket, response, sizeof(response), 0);
        }
        free(request);
        close(clientSocket);
        printf("\n");
    }
}

int Server::sendToService(const char *request, const char *src ,int Port) {
    struct sockaddr_in serverAddress;
    
    int serviceSocket;
    // create a socket
    serviceSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serviceSocket < 0) {
        perror("Error creating socket");
        return -1;
    }

    // set server details
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(Port);
    
    //this is for the my laptop
    // inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    inet_pton(AF_INET, src, &serverAddress.sin_addr);


    // connect to the target server
    if (connect(serviceSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error connecting to the target server");
        close(serviceSocket);
        return -1;
    }

    // send a message to the target server
    send(serviceSocket, request, strlen(request), 0);

    // loop to continuously read data from 
    //the target server until recv returns 0 (indicating the end of the stream).
    char buffer[SIZE];
    ssize_t bytesRead;
    do {
        bytesRead = recv(serviceSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            // Forward the response back to the original client
            send(clientSocket, buffer, bytesRead, 0);
        }
    } while (bytesRead > 0);

    // close the socket
    close(serviceSocket);
    return 0;
}

void Server::handleSignal(int signal) {
    Server& instance = getInstance();

    if (signal == SIGINT) {
        printf("\nShutting down server...\n");

        // Access members using the instance
        close(instance.clientSocket);
        close(instance.serverSocket);

        if (instance.request != nullptr)
            free(instance.request);

        // No need to delete the instance, as it's a static instance
        exit(0);
    }
}