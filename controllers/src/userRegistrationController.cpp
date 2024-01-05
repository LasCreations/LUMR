#include "userRegistrationController.h"

void handleUserRegistration(CLIENT *client)
{
    USER data = parseUserDetails(parseHttpRequest(client->request));
    // Search the map for users
    if (CACHE::getInstance().getUserMap().find(data.getUsername()) != CACHE::getInstance().getUserMap().end())
    {
        // user exists
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(client->socket, response, sizeof(response) - 1, 0);
        return; // exit function
    }

    USERINSTITUTION userInstdata = parseUserInstitutionDetails(parseHttpRequest(client->request));
    if (USER().create(data))
    {
        CACHE &cache = CACHE::getInstance();
        addRelations(userInstdata, data);
        // add to cache
        cache.insertUserToMap(data); 
        cache.insertUserSessionToMap(data);
        //Add token to the users browser
        std::string httpResponse = "HTTP/1.1 200 OK\r\nSet-Cookie: SID=" + data.getSID() + "; Path=/; Max-Age=3153600000\r\n\r\n";
        send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
    }
    else
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(client->socket, response, sizeof(response) - 1, 0);
    }
}

USER parseUserDetails(std::string jsonData)
{
    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::istringstream jsonStream(jsonData);
    Json::parseFromStream(readerBuilder, jsonStream, &root, nullptr);

    std::string firstname = root["firstname"].asString();
    std::string lastname = root["lastname"].asString();
    std::string username = root["username"].asString();
    std::string password = root["password"].asString();
    std::string avatar = root["avatar"].asString();
    // convert string to int then to uint16_t
    uint16_t rank = static_cast<uint16_t>(std::stoi(root["rank"].asString()));
    uint16_t yearStart = static_cast<uint16_t>(std::stoi(root["yearStart"].asString()));
    uint16_t yearEnd = static_cast<uint16_t>(std::stoi(root["yearEnd"].asString()));
    std::string institutionName = root["institutionName"].asString();

    USER temp = new USER(generateRandomCode(SIDSIZE), username, password, avatar, firstname, lastname, yearStart, yearEnd, rank);
    return temp;
}

USERINSTITUTION parseUserInstitutionDetails(std::string jsonData)
{
    USERINSTITUTION userInstdata;
    Json::CharReaderBuilder readerBuilder;
    Json::Value root;
    std::istringstream jsonStream(jsonData);
    Json::parseFromStream(readerBuilder, jsonStream, &root, nullptr);

    std::string username = root["username"].asString();
    std::string institutionName = root["institutionName"].asString();

    userInstdata.username = username;
    userInstdata.institution = institutionName;

    const Json::Value degreesArray = root["degrees"];
    for (const auto &degree : degreesArray)
        userInstdata.degrees.push_back(degree.asString());

    const Json::Value coursesArray = root["courses"];
    for (const auto &course : coursesArray)
        userInstdata.courses.push_back(course.asString());

    return userInstdata;
}

void addRelations(USERINSTITUTION userInstData, USER user)
{
    CACHE &cache = CACHE::getInstance();
    USER temp;
    
    const auto &it = cache.getInstitutionMap().find(userInstData.institution);
    if (it != cache.getInstitutionMap().end())
    {
        temp.addUserInstitution(it->second.getInstitutionCode(), user.getUsername());
        const auto &institutionDegrees = it->second.getInstitutionDegrees();
        for (const auto &Userdeg : userInstData.degrees)
        {
            const auto &deg = institutionDegrees.find(Userdeg);
            if (deg != institutionDegrees.end())
            {
                temp.addUserDegree(deg->second.getDegreeCode(), user.getUsername());
                const auto &coursesMap = deg->second.getCourses();
                for (const auto &Usercourse : userInstData.courses)
                {
                    const auto &courses = coursesMap.find(Usercourse);
                    if (courses != coursesMap.end())
                    {
                        temp.addUserCourse(courses->second.getCourseCode(), user.getUsername());
                    }
                }
            }
        }
    }
}