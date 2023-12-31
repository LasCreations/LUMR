#include "../lib/routes.h"

char method[10] = "";
char route[100] = "";

void apiRoute(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan,
              USERCONNECTIONCACHE *cacheConnectionData, NOTIFICATIONCACHE *cacheNotificationData)
{
    // parse HTTP request
    sscanf(request, "%s %s", method, route);
    // printf("%s %s\n", method, route);

    if (strcmp(method, "GET") == 0)
    {
        handlePageRequest(route, clientSocket);
    }
    else if (strcmp(method, "POST") == 0)
    {
        if (strcmp(route, "/user/register") == 0)
            addUser(request, clientSocket, userCacheData, dbMan);

        if (strcmp(route, "/user/login") == 0)
            checkUserCredentials(request, clientSocket, userCacheData, dbMan); 

        if (strcmp(route, "/user/me") == 0)
            userDataDashBoard(request, clientSocket, userCacheData, cacheConnectionData);

        if (strcmp(route, "/user/search") == 0)
            searchUser(request, clientSocket, userCacheData, cacheConnectionData);
        
        if (strcmp(route, "/user/follow") == 0)
            addConnection(request, clientSocket, dbMan, userCacheData, cacheConnectionData, cacheNotificationData);
        
        if (strcmp(route, "/user/followers") == 0)
            getFollowers(request, clientSocket, userCacheData, cacheConnectionData);

        if (strcmp(route, "/user/following") == 0)
            getFollowing(request, clientSocket, userCacheData, cacheConnectionData);
        
        if (strcmp(route, "/user/notification") == 0)
            getNotification(request, clientSocket,
                        userCacheData, 
                        cacheConnectionData, 
                        cacheNotificationData,
                        dbMan);
    }
    else
    {
        const char response[] = "HTTP/1.1 400 Bad Request\r\n\n";
        send(clientSocket, response, sizeof(response), 0);
    }
}
