#include "userAuthentication.h"

void handleUserAuthentication(CLIENT *client){
    std::string request(client->request);
    std::string SID = extractCookieValue(request);

    if(SID.empty()){
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(client->socket, response, sizeof(response) - 1, 0);
    }else{
        CACHE &cache = CACHE::getInstance();
        const auto &it = cache.getSessionIDMap().find(SID);
        if (it != cache.getSessionIDMap().end())
        {
            const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
            send(client->socket, response, sizeof(response) - 1, 0);
        }else{
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(client->socket, response, sizeof(response) - 1, 0);
        }
    }
}

std::string extractCookieValue(const std::string request) {
    std::string identifier = "SID=";
    size_t pos = request.find(identifier);
    if (pos != std::string::npos) {
        pos += identifier.length(); // Move to the beginning of the cookie value
        std::string cookieValue = request.substr(pos, SIDSIZE); // fixed length of characters

        return cookieValue;
    }
    return "";
}
