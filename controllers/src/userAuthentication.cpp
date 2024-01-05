#include "userAuthentication.h"

void handleUserAuthentication(CLIENT *client){
    std::string request(client->request);
    
    std::cout << extractCookieValue(request) << std::endl;
}

std::string extractCookieValue(const std::string request) {
    std::string identifier = "SID=";
    size_t pos = request.find(identifier);
    if (pos != std::string::npos) {
        pos += identifier.length(); // Move to the beginning of the cookie value
        size_t endPos = request.find(';', pos);
        if (endPos == std::string::npos) {
            endPos = request.length(); // If no semicolon is found, use the entire string
        }
        std::string cookieValue = request.substr(pos, endPos - pos);
        
        // Remove leading and trailing whitespaces (if any)
        size_t firstNonSpace = cookieValue.find_first_not_of(" \t\n\r\f\v");
        size_t lastNonSpace = cookieValue.find_last_not_of(" \t\n\r\f\v");
        
        if (firstNonSpace != std::string::npos && lastNonSpace != std::string::npos) {
            return cookieValue.substr(firstNonSpace, lastNonSpace - firstNonSpace + 1);
        }
    }
    return "";
}
