#include "degreeController.h"

void handleDegrees(CLIENT *client)
{
    CACHE &cache = CACHE::getInstance();
    for (const auto &inst : cache.getInstitutionMap())
    {
        if (parseDegreeRequest(parseHttpRequest(client->request)) == inst.second.getInstitutionName())
        {
            std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                createDegreeJsonArray(inst.second.getInstitutionDegrees());
            send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
            return;
        }
    }

}

std::string parseDegreeRequest(std::string request)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(request);
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        return jsonData["name"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return "";
}

std::string createDegreeJsonArray(std::vector<DEGREE> *degrees)
{
    Json::Value jsonArray;

    for (const auto &deg : (*degrees))
    {
        Json::Value jsonObject = createDegreeJsonObject(deg.getDegreeName());
        jsonArray.append(jsonObject);
    }
    std::cout << "\n\n" << jsonArray.toStyledString() << std::endl;
    return jsonArray.toStyledString();
}

Json::Value createDegreeJsonObject(std::string name)
{
    Json::Value jsonObject;

    jsonObject["name"] = name;

    return jsonObject;
}