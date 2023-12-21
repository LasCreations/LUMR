#include "common.h"

DBConnector *dbConn = new DBConnector(); // Initialization


string cookie = "";
string userID = "";
string searchID = "";

string parseHttpRequest(char *request)
{
    const std::regex jsonRegex(R"(\{[^{}]*\})"); // Define a regex pattern to match JSON
    std::string dataStr(request);                // Convert C-style string to std::string
    std::smatch match;                           // Search for the first match in the response

    if (std::regex_search(dataStr, match, jsonRegex))
    {
        std::cout << "JSON data: " << match.str() << std::endl;
    }
    else
    {
        std::cout << "No JSON data found in the response." << std::endl;
    }

    return match.str();
}

string generateRandomCode(int length)
{
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string Code;

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < length; ++i)
    {
        const int randomIndex = std::rand() % characters.length();
        Code += characters[randomIndex];
    }

    return Code;
}

bool checkFriendship(string userID_1, string userID_2){
    if (dbConn->createConnection())
    {   

        std::cout << "Connected to database" << std::endl;
        if(dbConn->checkFriendship(userID_1, userID_2))
            return true;
        else
            return false;

    }
    else
    {
        std::cout << "Failed to connect to database" << std::endl;
        return false;
    }
}