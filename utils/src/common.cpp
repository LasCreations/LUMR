#include "common.h"

std::string parseHttpRequest(char *request){
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