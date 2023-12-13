#include "../lib/common.h"
#include "../lib/authenticate.h"
#include "../../database/lib/DBConnector.h"
#include "../../database/models/user.h"

std::string generateRandomCookieCode(int length)
{
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string cookieCode;

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i)
    {
        const int randomIndex = std::rand() % characters.length();
        cookieCode += characters[randomIndex];
    }

    return cookieCode;
}

void handleJSONRequests(string data, int clientSocket)
{
    cout << "\n\nHERE" << endl;
    cout << data << endl;
    const char response[] = "HTTP/1.1 200 OK\r\n\n";
    send(clientSocket, response, sizeof(response), 0);
}

void handleSignUpRequest(char *data, int clientSocket)
{

    std::string username, email, password, cookie;
    cookie = generateRandomCookieCode(15);
    ParseData(username, email, password, data);
    User *user = new User(username, email, password, cookie);

    DBConnector *dbConn = new DBConnector();
    if (dbConn->createConnection())
    {
        std::cout << "Connected to database" << std::endl;
        if (dbConn->addUser(user))
        {
            // Construct the HTTP response with a dynamically generated Set-Cookie header
            char response[256]; // Adjust the size accordingly
            std::snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                          cookie.c_str());

            send(clientSocket, response, sizeof(response) - 1, 0);
        }
        else
        {
            const char response[] =
                "HTTP/1.1 400 BAD REQUEST\r\n"
                "\r\n";
            send(clientSocket, response, sizeof(response) - 1, 0);
        }
    }
    else
    {
        std::cout << "Failed to connect to database" << std::endl;
    }
}

string ParseJSON(char *body)
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
        // std::cout << "Matched JSON data: " << match.str() << std::endl;
    }
    else
    {
        // std::cout << "No JSON data found in the response." << std::endl;
    }

    return match.str();
}

void handlePostRequests(char *request, char *body, char *route, int clientSocket)
{

    if (strcmp(route, "/submit") == 0)
    {
        handleSignUpRequest(body, clientSocket);
    }
    if (strcmp(route, "/json") == 0)
    {
        handleJSONRequests(ParseJSON(body), clientSocket);
    }
}

void ParseData(std::string &username, std::string &email, std::string &password, char *postData)
{

    std::string inputStr(postData);

    // Define regular expressions for username, email, and password
    std::regex usernameRegex("username=([^&]+)");
    std::regex emailRegex("email=([^&]+)");
    std::regex passwordRegex("password=([^&]+)(?:&|$)");

    // Match the regular expressions in the input string
    std::smatch usernameMatch, emailMatch, passwordMatch;

    if (std::regex_search(inputStr, usernameMatch, usernameRegex) &&
        std::regex_search(inputStr, emailMatch, emailRegex) &&
        std::regex_search(inputStr, passwordMatch, passwordRegex))
    {

        // Extract username, email, and password from the matches
        username = usernameMatch[1];
        email = emailMatch[1];
        password = passwordMatch[1];

        size_t percentPos = email.find("%40");
        if (percentPos != std::string::npos)
        {
            email.replace(percentPos, 3, "@");
        }
    }
    else
    {
        std::cout << "No match found." << std::endl;
    }
}