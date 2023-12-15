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
        if (addUserToDatabase(username, email, password, cookie))
        {
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

    if (strcmp(route, "/user/auth") == 0)
    {
        if (getUserData(parseCookie(request)) != nullptr)
        {
            std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" + 
                                        ParseUserDataToJSON(getUserData(parseCookie(request))->getUsername(),
                                        getUserData(parseCookie(request))->getPassword(),
                                        getUserData(parseCookie(request))->getEmail());
                // Send the HTTP response
                send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
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

    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);

        // Access individual fields
        username = jsonData["username"].asString();
        email = jsonData["email"].asString();
        password = jsonData["password"].asString();
    }
    catch (const Json::Exception &e)
    {
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

string parseCookie(char *request)
{



    // std::istringstream iss(request);
    // std::string line;
    // std::string cookieValue;
    // // Find the line starting with "Cookie: "
    // while (std::getline(iss, line))
    // {
    //     size_t pos = line.find("Cookie: ");
    //     if (pos != std::string::npos)
    //     {
    //         // Extract the value after "Cookie: "
    //         cookieValue = line.substr(pos + strlen("Cookie: "));

    //         // Remove "sessionID="
    //         size_t sessionIdPos = cookieValue.find("sessionID=");
    //         if (sessionIdPos != std::string::npos)
    //         {
    //             cookieValue.erase(sessionIdPos, strlen("sessionID="));
    //         }

    //         // Print the extracted and modified cookie value
    //         // std::cout << "Cookie: " << cookieValue << std::endl;
    //     }
    // }
    // cout << "Cookie: " << cookieValue << endl;
    // return cookieValue;

    std::istringstream iss(request);
    std::string line;
    std::string sessionID;

    // Find the line starting with "Cookie: "
    while (std::getline(iss, line)) {
        if (line.find("Cookie: ") != std::string::npos) {
            // Extract the value after "Cookie: "
            std::string cookieValue = line.substr(line.find("Cookie: ") + strlen("Cookie: "));

            // Find the position of "sessionID="
            size_t sessionIDPos = cookieValue.find("sessionID=");

            // Check if "sessionID=" is found and extract the sessionID
            if (sessionIDPos != std::string::npos) {
                

                // Find the end of the sessionID value
                size_t sessionIDEnd = cookieValue.find(';', sessionIDPos);

                // If the sessionID is the last cookie, take the substring until the end of the line
                if (sessionIDEnd == std::string::npos) {
                    sessionID = cookieValue.substr(sessionIDPos + strlen("sessionID="));
                } else {
                    // Otherwise, take the substring until the next semicolon
                    sessionID = cookieValue.substr(sessionIDPos + strlen("sessionID="), sessionIDEnd - (sessionIDPos + strlen("sessionID=")));
                }

                // Print the extracted sessionID
                std::cout << "sessionID: " << sessionID << std::endl;
            } else {
                std::cerr << "sessionID not found in Cookie" << std::endl;
            }
        }
    }
    return sessionID;
}

User *getUserData(string cookie)
{
    User *data = nullptr;
    if (dbConn->createConnection())
    {
        data = dbConn->getUserData(cookie);
    }
    return data;
}

string ParseUserDataToJSON(string username, string password, string email)
{
    // Create a JSON object
    Json::Value jsonValue;

    // Add key-value pairs to the JSON object
    jsonValue["username"] = username;
    jsonValue["email"] = email;
    jsonValue["password"] = password;

    // Convert the JSON object to a JSON string
    std::string jsonString = jsonValue.toStyledString();

    // Print the resulting JSON string
    std::cout << "\n\n"
              << jsonString << std::endl;
    return jsonString;
}