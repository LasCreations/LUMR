#include "../lib/server.h"

void *handleRequests(void *pClientSocket){
        int clientThreadSocket = *((int *)pClientSocket);
        // free(pClientSocket);
        char *request = (char *)malloc(SIZE * sizeof(char));
        ssize_t bytesRead = read(clientThreadSocket, request, SIZE);
        if (bytesRead < 0)
        {
            perror("Error reading from client socket");
            close(clientThreadSocket);
            return NULL; // or return 1; depending on your application logic
        }

        apiRoute(request, clientThreadSocket, cacheUserData, dbMan);

        free(request);
        close(clientThreadSocket);
        // close(clientThreadSocket);
        printf("\n");
        return NULL;
}

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
    


    dbMan = new DATABASEMANAGER();

    cacheUserData = new USERCACHE();
    cacheUserData->preloadUserData(dbMan);

    while (1)
    {
        // accept connection and read data
        int clientSocket = accept(serverSocket, NULL, NULL);
        
        //implementation of multithreading 
        pthread_t t;
        pthread_create(&t, NULL, handleRequests, (void *)&clientSocket);
        pthread_join(t, NULL);
    }
}

static void handleSignal(int signal)
{
    if (signal == SIGINT)
    {
        printf("\nShutting down server...\n");

        // close(clientSocket);
        close(serverSocket);

        // if (request != NULL)
        //     free(request);

        exit(0);
    }
}

int main()
{
    runServer();
    return EXIT_SUCCESS;
}