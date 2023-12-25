#include "../lib/jsonParser.h"

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

PROFILE *parseProfileTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    PROFILE *data = nullptr;
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        // set the token as the profile id
        data = new PROFILE(jsonData["token"].asString(), "", jsonData["email"].asString(), jsonData["avatarurl"].asString(),
                           jsonData["bio"].asString(), jsonData["gender"].asString(), false);
        return data;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return data;
}

USER *parseTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    USER *user = nullptr;
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        user = new USER(jsonData["username"].asString(), jsonData["password"].asString(),
                        generateRandomCode(24), new PROFILE());
        return user;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return user;
}

string ParseUserDataToJSON(USER *user)
{
    // Create a JSON object
    Json::Value jsonValue;

    // Add key-value pairs to the JSON object
    jsonValue["username"] = user->getUsername();
    jsonValue["avatarurl"] = user->getProfile()->getAvatarURL();
    jsonValue["bio"] = user->getProfile()->getBio();
    // Convert the JSON object to a JSON string
    std::string jsonString = jsonValue.toStyledString();

    // Print the resulting JSON string
    std::cout << "\n\n"
              << jsonString << std::endl;
    return jsonString;
}