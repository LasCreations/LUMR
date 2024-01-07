#include "courseController.h"

void handleCourses(CLIENT *client)
{
    CACHE &cache = CACHE::getInstance();
    COURSEREQUEST courseReq = parseCourseRequest(parseHttpRequest(client->request));

    const auto &it = cache.getInstitutionMap().find(courseReq.institution);
    if (it != cache.getInstitutionMap().end())
    {
        const auto &institutionDegrees = it->second.getInstitutionDegrees();
        const auto &deg = institutionDegrees.find(courseReq.degree);
        if (deg != institutionDegrees.end())
        {
            std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                       createCoursesJsonArray(deg->second.getCourses());
            send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
            return; // exit function
        }
    }

    const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
    send(client->socket, response, sizeof(response) - 1, 0);
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

std::string createCoursesJsonArray(std::unordered_map<std::string, COURSE> courses)
{
    Json::Value jsonArray;
    for (const auto &course : courses)
    {
        Json::Value jsonObject = createCourseJsonObject(course.second.getCourseName());
        jsonArray.append(jsonObject);
    }
    std::cout << "\n\n" << jsonArray.toStyledString() << std::endl;
    return jsonArray.toStyledString();
}