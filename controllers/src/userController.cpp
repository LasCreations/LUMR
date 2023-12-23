#include "../lib/userController.h"

bool userExistsInCache(char *request, int clientSocket, USERCACHE *userCacheData)
{
    if (!userCacheData->isEmpty())
    {
        USER *data = parseSignupTokens(parseHttpRequest(request));
        if (userCacheData->userExists(data->getUsername()))
        {
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
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

void addUser(char *request, int clientSocket, USERCACHE *userCacheData)
{
    USER *data = parseSignupTokens(parseHttpRequest(request));

    if (data != nullptr)
    {
        data->getProfile()->setProfileID(generateRandomCode(12));
        data->getProfile()->setUserID(data->getUsername());
        data->setToken(generateRandomCode(24));
        if (addDataToUserTable(data) && addDataToUserProfileTable(data))
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

USER *parseSignupTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    USER *user = nullptr;
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        user = new USER(jsonData["username"].asString(), jsonData["password"].asString(),
                        generateRandomCode(24), new PROFILE());
        return user;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return user;
}