#include "../lib/UserApiHandler.h"

void handleUserRequests(char *request, char *method, const char *route, int clientSocket)
{
    string username, email, password, cookie;
    char *body = strstr(request, "\r\n\r\n");

    if (body != NULL)
    {
        // Null-terminate the headers part
        *body = '\0';
        body += 4; // Move to the start of the body
    }

    if (strcmp(route, "/user/register") == 0)
    {
        cookie = generateRandomCookieCode(15);
        parseJSONTokens(username, email, password, parseHttpRequest(body));
        if(addUserToDatabase(username, email, password, cookie)){
            char response[256]; // Adjust the size accordingly
            std::snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          cookie.c_str());
            send(clientSocket, response, sizeof(response) - 1, 0);
        }else{
            const char response[] =
                "HTTP/1.1 400 BAD REQUEST\r\n"
                "\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }
}

string parseHttpRequest(char *body)
{
    // Define a regex pattern to match JSON
    const std::regex jsonRegex(R"(\{[^{}]*\})");

    // Convert C-style string to std::string
    std::string dataStr(body);

    // Search for the first match in the response
    std::smatch match;
    if (std::regex_search(dataStr, match, jsonRegex))
    {
        // Extract and print the matched JSON part
        std::cout << "Matched JSON data: " << match.str() << std::endl;
    }
    else
    {
        std::cout << "No JSON data found in the response." << std::endl;
    }

    return match.str();
}

void parseJSONTokens(string &username, string &email, string &password, string JsonString)
{
     // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);

    try {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);

        // Access individual fields
        username = jsonData["username"].asString();
        email = jsonData["email"].asString();
        password = jsonData["password"].asString();
    } catch (const Json::Exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
}

string generateRandomCookieCode(int length)
{
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string cookieCode;

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i)
    {
        const int randomIndex = std::rand() % characters.length();
        cookieCode += characters[randomIndex];
    }

    return cookieCode;
}

bool addUserToDatabase(string username, string email, string password, string cookie)
{
    User *user = new User(username, email, password, cookie);   
    DBConnector *dbConn = new DBConnector();
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