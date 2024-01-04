#include "courseController.h"

void handleCourses(CLIENT *client)
{
    CACHE &cache = CACHE::getInstance();
    COURSEREQUEST courseReq = parseCourseRequest(parseHttpRequest(client->request));

    std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                               createCoursesJsonArray(courseReq, cache.getInstitutionMap());
    send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
}

COURSEREQUEST parseCourseRequest(std::string request)
{
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(request);
    COURSEREQUEST courseReq;
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        courseReq.degree = jsonData["degree"].asString();
        courseReq.institution = jsonData["institution"].asString();
        return courseReq;
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
    return courseReq;
}

std::string createCoursesJsonArray(COURSEREQUEST courseReq, std::unordered_map<std::string, INSTITUTION> &institutions)
{
    Json::Value jsonArray;

    for (const auto &inst : institutions)
    {
        if (courseReq.institution == inst.second.getInstitutionName())
        {
            for (const auto &deg : (*inst.second.getInstitutionDegrees()))
            {
                if (courseReq.degree == deg.getDegreeName())
                {
                    for (const auto &course : (*deg.getCourses()))
                    {
                        Json::Value jsonObject = createCourseJsonObject(course.getCourseName());
                        jsonArray.append(jsonObject);
                    }
                }
            }
        }
    }
    std::cout << "\n\n" << jsonArray.toStyledString() << std::endl;
    return jsonArray.toStyledString();
}

Json::Value createCourseJsonObject(std::string name)
{
    Json::Value jsonObject;

    jsonObject["course"] = name;

    return jsonObject;
}