#include "../lib/jsonParser.h"

string parseTokenFromRequest(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);

        if (jsonData["token"].isNull())
        {
            return "";
        }
        else
        {
            return jsonData["token"].asString();
        }
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return "";
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

USER *parseRegisterTokens(string JsonString)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(JsonString);
    USER *user = nullptr;
    try
    {
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        user = new USER(jsonData["username"].asString(), jsonData["password"].asString(),
                        generateRandomCode(24), new PROFILE(generateRandomCode(24), jsonData["username"].asString(), jsonData["email"].asString(), jsonData["avatar"].asString(), jsonData["bio"].asString(), jsonData["gender"].asString(), true));
        return user;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return user;
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

string UnparseUserDataToJSON(USER *user, bool isFriend, uint32_t followercount, uint32_t followingcount)
{
    
    Json::Value jsonValue;

    jsonValue["username"] = user->getUsername();
    jsonValue["avatarurl"] = user->getProfile()->getAvatarURL();
    jsonValue["bio"] = user->getProfile()->getBio();
    jsonValue["status"] = isFriend;
    jsonValue["followercount"] = followercount;
    jsonValue["followingcount"] = followingcount;
    // Convert the JSON object to a JSON string
    std::string jsonString = jsonValue.toStyledString();

    std::cout << "\n\n" << jsonString << std::endl;
    return jsonString;
}

string createJSONObjectArray(vector<CONNECTION> users, string username, USERCONNECTIONCACHE *cacheConnectionData)
{

    Json::Value jsonArray;

    for (size_t i = 0; i < users.size(); i++)
    {
        USER data = cacheConnectionData->getConnectionUser(username, users[i]);
        Json::Value jsonObject = createJSONObjectFollowView(data.getUsername(),
                                                            data.getProfile()->getAvatarURL(),
                                                            cacheConnectionData->isFollowing(username, data.getUsername()));
        jsonArray.append(jsonObject);
    }
    std::cout << "\n\n" << jsonArray.toStyledString() << std::endl;
    return jsonArray.toStyledString();
}

Json::Value createJSONObjectFollowView(string username, string avatarurl, bool status)
{
    Json::Value jsonObject;

    jsonObject["username"] = username;
    jsonObject["avatarurl"] = avatarurl;
    jsonObject["status"] = status;

    return jsonObject;
}

string createNotificationObjectArray(vector<NOTIFICATION> notification, 
                                        USERCONNECTIONCACHE *cacheConnectionData,
                                        USERCACHE *userCache){
    Json::Value jsonArray;
    for (size_t i = 0; i < notification.size(); i++){
        USER *user = userCache->getUserFromCache(notification[i].getSenderID());
        Json::Value jsonObject = createJSONObjectNotification(notification[i],
                                                            user->getProfile()->getAvatarURL(),
                                                            cacheConnectionData->isFollowing(
                                                                notification[i].getRecieverID(), 
                                                                notification[i].getSenderID())  );
        jsonArray.append(jsonObject);
    }
    std::cout << "\n\n" << jsonArray.toStyledString() << std::endl;
    return jsonArray.toStyledString();
}

Json::Value createJSONObjectNotification(NOTIFICATION notification, string avatarurl, bool status){
    Json::Value jsonObject;
    jsonObject["type"] = notification.getType();
    jsonObject["content"] = notification.getContent();
    jsonObject["timestamp"] = notification.getTimestamp();
    jsonObject["recieverID"] = notification.getRecieverID();
    jsonObject["senderID"] = notification.getSenderID();
    jsonObject["avatarurl"] = avatarurl;
    jsonObject["friendStatus"] = status;
    jsonObject["notificationStatus"] = notification.getStatus();
    return jsonObject;
}