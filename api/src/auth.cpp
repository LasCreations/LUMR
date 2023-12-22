#include "../lib/auth.h"

void registerUser(char *request, int clientSocket, UserDataCache *cacheData)
{
    User *data = parseJSONTokens(parseHttpRequest(request));

    if (!cacheData->userExists(data->getUsername(), data->getEmail()))
    {
        if (addUserToDatabase(data))
        {
            cacheData->addUserToMap(data);
            cacheData->preloadUserData();
            char response[256];
            std::snprintf(response, sizeof(response),
                          "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          data->getCookie().c_str());
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
        else
        {
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }else{
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void loginUser(char *request, int clientSocket, UserDataCache *cacheData)
{
    parseLoginTokens(parseHttpRequest(request));
    if (!cacheData->isEmpty())
    {
        User *data = cacheData->getUserFromCache(username, password);

        if (data != nullptr)
        {
            if (updateUserCookieDB(data))
            {
                cacheData->preloadUserData();
                User *data = cacheData->getUserFromCache(username, password);
                char response[256];
                std::snprintf(response, sizeof(response),
                              "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                              data->getCookie().c_str());
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
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void parseLoginTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        username = jsonData["username"].asString();
        password = jsonData["password"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
}

User *parseJSONTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    User *user = nullptr;
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        user = new User(jsonData["username"].asString(), jsonData["email"].asString(),
                        jsonData["password"].asString(), generateRandomCode(24),
                        jsonData["avatarurl"].asString());
        return user;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return user;
}

bool updateUserCookieDB(User *data)
{
    if (dbConn->createConnection())
    {
        std::cout << "Connected to database" << std::endl;
        if (dbConn->updatePassport(generateRandomCode(24), data))
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
        std::cout << "Failed to connect to database" << std::endl;
        return false;
    }
}

bool addUserToDatabase(User *data)
{
    if (dbConn->createConnection())
    {
        std::cout << "Connected to database" << std::endl;
        if (dbConn->addUser(data))
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
        std::cout << "Failed to connect to database" << std::endl;
        return false;
    }
}