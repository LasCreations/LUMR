#include "common.h"

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
    const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string Code;

    // Seed the random number generator only once
    static bool seedInitialized = false;
    if (!seedInitialized)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seedInitialized = true;
    }

    for (int i = 0; i < length; ++i)
    {
        const int randomIndex = std::rand() % characters.length();
        Code += characters[randomIndex];
    }

    return Code;
}

string parseTokenFromRequest(string JsonString){
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        return jsonData["token"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return NULL;
}