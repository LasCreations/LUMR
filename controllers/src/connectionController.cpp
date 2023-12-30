#include "../lib/connectionController.h"

void addConnection(char *request, int clientSocket,
                   DATABASEMANAGER *dbMan, USERCACHE *userCacheData,
                   USERCONNECTIONCACHE *cacheConnectionData,
                   NOTIFICATIONCACHE *cacheNotificationData)
{
    // get the current user
    USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));

    // get the user being searched for
    USER *tempdata = parseTokens(parseHttpRequest(request));
    USER *userSearch = userCacheData->getUserFromCache(tempdata->getUsername());

    CONNECTION *userCon = new CONNECTION(data, userSearch, true, false);

    // check if a connection was made already
    CONNECTION *checkCacheConnections = cacheConnectionData->getConnectionFromCache(data->getUsername(), userSearch->getUsername());
    if (checkCacheConnections != nullptr) // if it is nullptr the user is following back
    {
        cacheConnectionData->updateUser2FollowBackStatus(userSearch->getUsername(), data->getUsername());
        if (updateUser2Status(true, data->getUsername(), dbMan))
        {
            // passed the current time using time(nullptr)
            NOTIFICATION *notification = new NOTIFICATION(generateRandomCode(15), userSearch->getUsername(),
                                                          data->getUsername(), "Follow",
                                                          data->getUsername() + " is following you.", false, getCurrentTime());

            if (addNotificationToDatabase(dbMan, notification))
            {
                cacheConnectionData->preloadConnectionData(dbMan, userCacheData);
                cacheNotificationData->addNotificationToCache(notification);
                const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
                send(clientSocket, response, sizeof(response) - 1, 0);
            }
            else
            {
                const char response[] = "HTTP/1.1 500 SERVER ERROR\r\n\r\n";
                send(clientSocket, response, sizeof(response) - 1, 0);
            }
        }
    }
    else
    {
        // passed the current time using time(nullptr)
        NOTIFICATION *notification = new NOTIFICATION(generateRandomCode(15), userSearch->getUsername(),
                                                      data->getUsername(), "Follow",
                                                      data->getUsername() + " is following you.", false, getCurrentTime());

        if (addConnectionToDatabase(dbMan, userCon) && addNotificationToDatabase(dbMan, notification))
        {
            cacheConnectionData->preloadConnectionData(dbMan, userCacheData);
            cacheNotificationData->addNotificationToCache(notification);
            const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
        else
        {
            const char response[] = "HTTP/1.1 500 SERVER ERROR\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }
}