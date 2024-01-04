#include "server.h"

int serverSocket; // socket for the server

int confiureServer()
{
    signal(SIGINT, handleSignal); // run handler function when a signal is recieved

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    int option = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0)
    {
        perror("Error setting socket options");
        return 1;
    }

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
        int clientSocket = accept(serverSocket, NULL, NULL);
        std::cout << "--- Accepted new connection --- \nClient socket: " << clientSocket << std::endl;
        readRequest(clientSocket);
    }
    return 1;
}

int readRequest(int clientSocket)
{
    char *request = (char *)malloc(SIZE * sizeof(char));
    char method[10], route[SIZE];

    if (request == NULL)
    {
        perror("Error allocating memory");
        return 1;
    }

    ssize_t bytesRead = read(clientSocket, request, SIZE);
    printf("\nBytes Read: %d", bytesRead);
    if (bytesRead == -1)
    {
        perror("Error reading from socket");
        free(request); // Free allocated memory before returning
        return 1;
    }

    sscanf(request, "%s %s", method, route);
    printf("\n%s %s\n", method, route);
    handleThreadAlloctions(clientSocket, request, method, route);
    // free(request); //free allocated memory
    return 0; // success
}

void handleThreadAlloctions(int clientSocket, char *request, char *method, char *route)
{
    struct CLIENT client;

    client.socket = clientSocket;
    client.request = request;
    client.method = method;
    client.route = route;

    pthread_t thread;

    if (strcmp(route, "/user/notification") == 0)
    {
        pthread_create(&thread, NULL, detachedThreads, (void *)&client);
        pthread_detach(thread); // LONG POLLING
    }
    else
    {
        pthread_create(&thread, NULL, joinedThread, (void *)&client);
        pthread_join(thread, NULL); 
    }
}

void *joinedThread(void *clientThread)
{
    struct CLIENT *client = (struct CLIENT *)clientThread;
    // printClientInformation(client);
    handleRouting(client);
    close(client->socket);
    return NULL;
}

void *detachedThreads(void *clientThread)
{
    struct CLIENT *client = (struct CLIENT *)clientThread;
    // printClientInformation(client);
    handleRouting(client);
    return NULL;
}

void printClientInformation(CLIENT *client){
    std::cout << "\nClient Socket: " << client->socket << std::endl;
    std::cout << "\n-------------Request Header------------\n" << std::endl;
    std::cout << client->request << std::endl;
    std::cout << "\n---------------------------------------" << std::endl;
    printf("\n");
}

void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        printf("\nShutting down server...\n");
        close(serverSocket);
        exit(0);
    }
}