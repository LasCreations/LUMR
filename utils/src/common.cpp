#include "common.h"

std::string parseHttpRequest(char *request)
{
    const std::regex jsonRegex(R"(\{[^{}]*\})");
    std::string dataStr(request);
    std::smatch match;

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

std::string generateRandomCode(int length)
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

std::string getCurrentTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    
    return std::ctime(&currentTime);
}

Json::Value createDegreeJsonObject(std::string name)
{
    Json::Value jsonObject;

    jsonObject["name"] = name;

    return jsonObject;
}

Json::Value createCourseJsonObject(std::string name)
{
    Json::Value jsonObject;

    jsonObject["name"] = name;

    return jsonObject;
}