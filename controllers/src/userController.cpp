#include "../lib/userController.h"

bool userExistsInCache(char *request, int clientSocket, USERCACHE *userCacheData)
{
    if (!userCacheData->isEmpty())
    {
        USER *data = parseTokens(parseHttpRequest(request));
        if (userCacheData->userExists(data->getUsername()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void addUser(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan)
{

    USER *data = parseRegisterTokens(parseHttpRequest(request)); // parse the register request

    // Check cache memory
    USER *cacheData = userCacheData->getUserFromCache(data->getUsername()); // check if user exists

    if (cacheData == nullptr)
    {
        if (addDataToUserTable(dbMan, data) && addDataToUserProfileTable(dbMan, data))
        {
            userCacheData->addUserToMap(data);
            char response[256];
            std::snprintf(response, sizeof(response),
                          "HTTP/1.1 200 OK\r\nSet-Cookie: Token=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          data->getToken().c_str());
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
        else
        {
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void userDataDashBoard(char *request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData)
{

    if (!userCacheData->isEmpty())
    {
        USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
        if (data != nullptr)
        {

            vector<CONNECTION> followers = cacheConnectionData->getFollowerConnections(data->getUsername());
            vector<CONNECTION> following = cacheConnectionData->getFollowingConnections(data->getUsername());

            createJSONObjectArray(following, data->getUsername(), cacheConnectionData);

            std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                       UnparseUserDataToJSON(data, false, cacheConnectionData->followerCount(data->getUsername()),
                                                             cacheConnectionData->followingCount(data->getUsername()));

            send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
        }
        else
        {
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void searchUser(char *request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData)
{
    // get sender information
    USER *user1 = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));

    // parse name
    USER *data = parseTokens(parseHttpRequest(request));
    USER *user2 = userCacheData->getUserFromCache(data->getUsername());

    if ((user1 != nullptr) && (user2 != nullptr))
    {
        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                   UnparseUserDataToJSON(user2, cacheConnectionData->isFollowing(user1->getUsername(), user2->getUsername()), cacheConnectionData->followerCount(user2->getUsername()),
                                                         cacheConnectionData->followingCount(user2->getUsername()));
        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    }
    else
    {
        const char response[] = "HTTP/1.1 500 SERVER ERROR\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void getFollowers(char *request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData)
{
    USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
    if (data != nullptr)
    {
        vector<CONNECTION> followers = cacheConnectionData->getFollowerConnections(data->getUsername());

        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                   createJSONObjectArray(followers, data->getUsername(), cacheConnectionData);

        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void getFollowing(char *request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData)
{
    USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
    if (data != nullptr)
    {
        vector<CONNECTION> following = cacheConnectionData->getFollowingConnections(data->getUsername());

        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                   createJSONObjectArray(following, data->getUsername(), cacheConnectionData);

        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void getNotification(char *request, int clientSocket,
                     USERCACHE *userCacheData,
                     USERCONNECTIONCACHE *cacheConnectionData,
                     NOTIFICATIONCACHE *cacheNotificationData,
                     DATABASEMANAGER *dbMan)
{
    USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
    vector<NOTIFICATION> newNotifications;

    while (true)
    {
        if (cacheNotificationData->hasNewNotification(data->getUsername()))
        {
            vector<NOTIFICATION> notification = cacheNotificationData->getNotifications(data->getUsername());
            for (size_t i = 0; i < notification.size(); i++)
            {
                if (!notification[i].getStatus())
                {
                    newNotifications.push_back(notification[i]);
                    updateNotificationStatus(notification[i], dbMan);
                    cacheNotificationData->updateNotificationStatus(notification[i]);
                }
            }
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                               createNotificationObjectArray(newNotifications,
                                                             cacheConnectionData,
                                                             userCacheData);

    send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    close(clientSocket);
}