#include "../lib/common.h"

DBConnector *dbConn = new DBConnector(); // Initialization

std::string username = "";
std::string email = "";
std::string password = "";
std::string avatarurl = "";
std::string cookie = "";


string parseHttpRequest(char *request)
{
    const std::regex jsonRegex(R"(\{[^{}]*\})"); // Define a regex pattern to match JSON
    std::string dataStr(request);                // Convert C-style string to std::string
    std::smatch match;                           // Search for the first match in the response

    if (std::regex_search(dataStr, match, jsonRegex))
    {
        std::cout << "Matched JSON data: " << match.str() << std::endl;
    }
    else
    {
        std::cout << "No JSON data found in the response." << std::endl;
    }

    return match.str();
}