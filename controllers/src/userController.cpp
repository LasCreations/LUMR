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
    else
    {
        return false;
    }
    return false;
}

void addUser(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan)
{
    USER *data = parseTokens(parseHttpRequest(request));

    if (data != nullptr)
    {
        data->getProfile()->setProfileID(generateRandomCode(12));
        data->getProfile()->setUserID(data->getUsername());
        data->setToken(generateRandomCode(24));
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

void updateUserProfile(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan)
{

    if (updateUserProfile(dbMan, userCacheData->updateUserProfileInCache(parseProfileTokens(parseHttpRequest(request)))))
    {
        const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void userDataDashBoard(char *request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData)
{

    USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
    if (data != nullptr)
    {
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

void checkUserCredentials(char *request, int clientSocket, USERCACHE *userCacheData, DATABASEMANAGER *dbMan)
{
    USER *data = parseTokens(parseHttpRequest(request));
    USER *cacheData = userCacheData->getUserFromCache(data->getUsername(), data->getPassword());

    if (cacheData != nullptr)
    {
        if (updateUserToken(cacheData, userCacheData, dbMan))
        {
            char response[256];
            std::snprintf(response, sizeof(response),
                          "HTTP/1.1 200 OK\r\nSet-Cookie: Token=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          cacheData->getToken().c_str());
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
        else
        {
            const char response[] = "HTTP/1.1 500 Internal Server Error\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

bool updateUserToken(USER *user, USERCACHE *userCacheData, DATABASEMANAGER *dbMan)
{
    string token = generateRandomCode(24);
    if (updateToken(dbMan, user, token))
    {
        user->setToken(token);
        userCacheData->updateUserTokenInCache(user, token);
        return true;
    }
    return false;
}

void searchUser(char *request, int clientSocket, USERCACHE *userCacheData, USERCONNECTIONCACHE *cacheConnectionData)
{
    USER *user1 = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));

    USER *data = parseTokens(parseHttpRequest(request));
    USER *user2 = userCacheData->getUserFromCache(data->getUsername());

    if ((user1 != nullptr) && (user2 != nullptr))
    {
        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                   UnparseUserDataToJSON(user2, cacheConnectionData->isConnected(user1->getUsername(),
                                                        user2->getUsername()), cacheConnectionData->followerCount(user2->getUsername()),
                                                        cacheConnectionData->followingCount(user2->getUsername()));
        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    }
    else
    {
        const char response[] = "HTTP/1.1 500 SERVER ERROR\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}
