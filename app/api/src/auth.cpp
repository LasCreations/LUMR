#include "../lib/auth.h"

void registerUser(char *request, int clientSocket)
{
   
    cookie = generateRandomCode(24);
    parseJSONTokens(parseHttpRequest(request));
    if(addUserToDatabase(username, email, password, avatarurl, cookie)){
        char response[256]; 
        std::snprintf(response, sizeof(response),
                         "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          cookie.c_str());
        send(clientSocket, response, sizeof(response) - 1, 0);
    }else{
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void parseJSONTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);

    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);

        // Access individual fields
        username = jsonData["username"].asString();
        email = jsonData["email"].asString();
        password = jsonData["password"].asString();
        avatarurl = jsonData["avatarurl"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
}

bool addUserToDatabase(string username, string email, string password, string avatarurl, string cookie)
{
    User *user = new User(username, email, password, cookie, avatarurl);
    if (dbConn->createConnection())
    {
        std::cout << "Connected to database" << std::endl;
        if (dbConn->addUser(user))
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