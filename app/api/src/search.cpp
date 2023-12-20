#include "../lib/search.h"


void searchUser(char *request, int clientSocket)
{
    string user_id;
    parseUsernameToken(parseHttpRequest(request));
    User *userData = new User(searchUsername(searchID));
    cout << "user: " << userID << endl;
    cout << "search: " << searchID << endl;

    if (userData != nullptr){
        std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                   ParseSearchDataToJSON(userData->getUsername(), userData->getAvatarURL(),
                                                         checkFriendship(userID, searchID));
        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
    }else{
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void parseUsernameToken(string JsonString)
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

        searchID = jsonData["username"].asString(); // name being searched for
        userID = jsonData["userID"].asString();
        
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
}

User *searchUsername(string target)
{
    User *data = nullptr;
    if (dbConn->createConnection())
    {
        data = dbConn->searchUsername(target);
    }
    return data;
}

string ParseSearchDataToJSON(string username, string avatarurl, bool status)
{
    // Create a JSON object
    Json::Value jsonValue;

    // Add key-value pairs to the JSON object
    jsonValue["username"] = username;
    jsonValue["avatarurl"] = avatarurl;
    jsonValue["status"] = status;

    // Convert the JSON object to a JSON string
    std::string jsonString = jsonValue.toStyledString();

    // Print the resulting JSON string
    std::cout << "\n\n"
              << jsonString << std::endl;
    return jsonString;
}