#include "../lib/connections.h"

string userID, followerID;

void followUser(char *request, int clientSocket)
{
    parseFollowRequestTokens(parseHttpRequest(request));
    if(addFriendshipToDatabase()){
        const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }else{
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(clientSocket, response, sizeof(response) - 1, 0);
    }
}

void parseFollowRequestTokens(string JsonString)
{
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);

    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);

        // Access individual fields
        userID = jsonData["userID"].asString();
        followerID = jsonData["followerID"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
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

bool addFriendshipToDatabase()
{
    if (dbConn->createConnection())
    {
        std::cout << "Connected to database" << std::endl;
        
        if (dbConn->addFriendshipToDatabase(generateRandomCode(10),userID, followerID, true))
        {
            dbConn->addFriendshipToDatabase(generateRandomCode(11),followerID,userID, false);
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

