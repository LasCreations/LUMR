#include "institutionsController.h"

void handleInstitutions(CLIENT *client)
{
    CACHE &cache = CACHE::getInstance();
    std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                               createInstitutionJsonArray(cache.getInstitutionMap());
    send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
}

std::string createInstitutionJsonArray(std::unordered_map<std::string, INSTITUTION> &institutions)
{
    Json::Value jsonArray;

    for (const auto &inst : institutions)
    {
        Json::Value jsonObject = createInstitutionJsonObject(inst.second.getInstitutionName());
        jsonArray.append(jsonObject);
    }
    std::cout << "\n\n" << jsonArray.toStyledString() << std::endl;
    return jsonArray.toStyledString();
}

Json::Value createInstitutionJsonObject(std::string name)
{
    Json::Value jsonObject;

    jsonObject["name"] = name;

    return jsonObject;
}


