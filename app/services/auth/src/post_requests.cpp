#include "../lib/post_requests.h"

std::string generateRandomCookieCode(int length) {
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string cookieCode;

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i) {
        const int randomIndex = std::rand() % characters.length();
        cookieCode += characters[randomIndex];
    }

    return cookieCode;
}

void handlePostRequests(char *method, char *data, int clientSocket, Server &serverInstance)
{

    // Check method
    if (strcmp(method, "/submit") == 0)
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
                    // const char response[] =
                    // "Location: /about.html\r\n"
                    // "Content-Type: text/html\r\n"
                    // "HTTP/1.1 200 OK\r\n"
                    // "Set-Cookie: sessionID="cookie"; Path=/; Max-Age=3153600000\r\n"
                    // "\r\n";
            
                     // Construct the HTTP response with a dynamically generated Set-Cookie header
                    char response[256];  // Adjust the size accordingly
                    std::snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nSet-Cookie: sessionID=%s; Path=/; Max-Age=3153600000\r\n\r\n",
                                cookie.c_str());

                    send(clientSocket, response, sizeof(response) - 1, 0);
            }
            else
            {
                const char response[] =
                    // "Location: /about.html\r\n"
                    // "Content-Type: text/html\r\n"
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