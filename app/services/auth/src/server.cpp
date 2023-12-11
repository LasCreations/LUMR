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
        char method[10], data[100];
        
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
        sscanf(request, "%s %s", method, data);
        printf("%s %s", method, data);

        // only support GET method
        if (strcmp(method, "GET") == 0){
            
            //handleGetRequests(route,clientSocket);
        }else if (strcmp(method, "/submit") == 0){
            handlePostRequests(method, data, clientSocket, *this);
        }else if (strcmp(method, "/json") == 0){
                handleJSONRequests(method, request, clientSocket, *this);
        }else{
            const char response[] = "HTTP/1.1 400 Bad Request\r\n\n";
            send(clientSocket, response, sizeof(response), 0);
        }
        free(request);
        close(clientSocket);
        printf("\n");
    }
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

DBConnector Server::getConnection(){
    return this->dbConn;
}