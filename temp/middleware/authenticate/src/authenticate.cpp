#include "../lib/authenticate.h"

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

bool verifyUserToken(char *request, USERCACHE *userCacheData, int clientSocket)
{
    if (!parseTokenFromRequest(parseHttpRequest(request)).empty())
    {
        USER *data = userCacheData->getUserFromCacheByToken(parseTokenFromRequest(parseHttpRequest(request)));
        if (data != nullptr)
        {
            return true;
        }
    }
    return false;
}