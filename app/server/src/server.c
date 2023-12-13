#include "../lib/server.h"

int serverSocket;
int clientSocket;
char *request;

int runServer()
{
    // register signal handler
    signal(SIGINT, handleSignal);

    // server internet socket address
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;         // IPv4
    serverAddress.sin_port = htons(PORT);       // port number in network byte order (host-to-network short)
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface

    // socket of type IPv4 using TCP protocol
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // reuse address and port
    // setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    int option = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0)
    {
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

    if (error != 0)
    {
        printf("Error: %s\n", gai_strerror(error));
        return 1;
    }

    printf("\nServer is listening on http://%s:%s/\n\n", hostBuffer, serviceBuffer);

    while (1)
    {
        // buffer to store data (request)
        request = (char *)malloc(SIZE * sizeof(char));
        char method[10], route[100];

        // accept connection and read data
        clientSocket = accept(serverSocket, NULL, NULL);

        ssize_t bytesRead = read(clientSocket, request, SIZE);
        if (bytesRead < 0)
        {
            perror("Error reading from client socket");
            close(clientSocket);
            return 1; // or return 1; depending on your application logic
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
        if (strcmp(method, "GET") == 0)
        {
            if(handlePageRequest(route, clientSocket)){
                
            }
        }
        else if (strcmp(method, "POST") == 0)
        {
            if(strcmp(route, "/submit") == 0){
                handlePostRequests( request, body, route, clientSocket);
            }
            if(strcmp(route, "/json") == 0){
                handlePostRequests( request, body, route, clientSocket);
            }    
        }
        else
        {
            const char response[] = "HTTP/1.1 400 Bad Request\r\n\n";
            send(clientSocket, response, sizeof(response), 0);
        }
        free(request);
        close(clientSocket);
        printf("\n");
    }
}

static void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        printf("\nShutting down server...\n");

        close(clientSocket);
        close(serverSocket);

        if (request != NULL)
            free(request);

        exit(0);
    }
}