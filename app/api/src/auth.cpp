#include "../lib/auth.h"

void registerUser(char *request, int clientSocket)
{
    User *data = parseJSONTokens(parseHttpRequest(request));
    if(addUserToDatabase(data)){
        char response[256]; 
        std::snprintf(response, sizeof(response),
                         "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          data->getCookie().c_str());
        send(clientSocket, response, sizeof(response) - 1, 0);
    }else{
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

User *parseJSONTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    User* user = nullptr;
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