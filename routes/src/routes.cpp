#include "../lib/routes.h"

char method[10] = "";
char route[100] = "";

void apiRoute(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan, 
                USERCONNECTIONCACHE *cacheConnectionData)
{
    // parse HTTP request
    sscanf(request, "%s %s", method, route);
    printf("%s %s\n", method, route);

    if (strcmp(method, "GET") == 0)
    {
        handlePageRequest(route, clientSocket);
    }
    else if (strcmp(method, "POST") == 0)
    {
        if (strcmp(route, "/user/register") == 0)
        {
            if (!userExistsInCache(request, clientSocket, userCacheData))
            {
                addUser(request, clientSocket, userCacheData, dbMan);
            }
            else
            {
                const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
                send(clientSocket, response, sizeof(response) - 1, 0);
            }
        }

        if (strcmp(route, "/user/login") == 0)
        {
            if (userExistsInCache(request, clientSocket, userCacheData))
            {
                checkUserCredentials(request, clientSocket, userCacheData, dbMan);
            }
        }

        if (strcmp(route, "/user/profile/create") == 0)
            updateUserProfile(request, clientSocket, userCacheData, dbMan);

        if (strcmp(route, "/user/me") == 0)
            userDataDashBoard(request, clientSocket, userCacheData, cacheConnectionData);

        if (strcmp(route, "/user/search") == 0)
        {
            if (userExistsInCache(request, clientSocket, userCacheData))
            {
                searchUser(request, clientSocket, userCacheData, cacheConnectionData);
            }
            else
            {
                const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
                send(clientSocket, response, sizeof(response) - 1, 0);
            }
        }

        if (strcmp(route, "/user/follow") == 0)
            addConnection(request, clientSocket, dbMan,userCacheData, cacheConnectionData);
    }
    else
    {
        const char response[] = "HTTP/1.1 400 Bad Request\r\n\n";
        send(clientSocket, response, sizeof(response), 0);
    }
}
