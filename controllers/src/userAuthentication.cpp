#include "userAuthentication.h"

void handleUserAuthentication(CLIENT *client)
{
    std::string request(client->request);
    std::string SID = extractCookieValue(request);

    if (SID.empty())
    {
        const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
        send(client->socket, response, sizeof(response) - 1, 0);
    }
    else
    {
        CACHE &cache = CACHE::getInstance();
        const auto &it = cache.getSessionIDMap().find(SID);
        if (it != cache.getSessionIDMap().end())
        {
            const auto &userInst = cache.getUserInstitutionMap().find(it->second.getUsername());
            if (userInst != cache.getUserInstitutionMap().end())
            {
                std::cout << "Authenticated User: " << userInst->first << std::endl;
                std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n" +
                                           createUserJson(it->second, userInst->second);
                send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
            }
            else
            {
                const char response[] = "HTTP/1.1 200 OK\r\n\r\n";
                send(client->socket, response, sizeof(response) - 1, 0);
            }
        }
        else
        {
            const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
            send(client->socket, response, sizeof(response) - 1, 0);
        }
    }
}

void handleUserLoginAuthentication(CLIENT *client)
{

    std::string password, username;
    parseLoginRequest(parseHttpRequest(client->request), username, password);

    if (!username.empty() && !password.empty())
    {
        CACHE &cache = CACHE::getInstance();
        const auto &it = cache.getUserMap().find(username);
        if (it != cache.getUserMap().end() && password == it->second.getPassword())
        {
            const auto &userInst = cache.getUserInstitutionMap().find(it->second.getUsername());
            if (userInst != cache.getUserInstitutionMap().end())
            {
                //generate a new SID
                std::string newSID= generateRandomCode(SIDSIZE);
                if(USER().updateSID(newSID,it->first)){
                    // cache.
                    cache.getSessionIDMap().erase(it->second.getSID()); //erase old sesh
                    it->second.setSID(newSID); //update user
                    cache.insertUserSessionToMap( it->second); //insert new sesh

                    std::cout << "Authenticated User: " << userInst->first << std::endl;
                    std::string httpResponse = "HTTP/1.1 200 OK\r\nSet-Cookie: SID=" + newSID + "; Path=/; Max-Age=3153600000\r\nContent-Type: application/json\r\n\r\n" +
                                           createUserJson(it->second, userInst->second);
                    send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);
                    return;
                }
            }   
        }
    }
    const char response[] = "HTTP/1.1 400 BAD REQUEST\r\n\r\n";
    send(client->socket, response, sizeof(response) - 1, 0);
}

void parseLoginRequest(std::string request, std::string &username, std::string &password)
{
    // Your JSON string
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::istringstream jsonStream(request);
    try
    {
        // Parse the JSON string
        Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr);
        username = jsonData["username"].asString();
        password = jsonData["password"].asString();
    }
    catch (const Json::Exception &e)
    {
        std::cerr << "Error parsing JSON: " << e.what() << "\n";
    }
}

std::string extractCookieValue(const std::string request)
{
    std::string identifier = "SID=";
    size_t pos = request.find(identifier);
    if (pos != std::string::npos)
    {
        pos += identifier.length();                             // Move to the beginning of the cookie value
        std::string cookieValue = request.substr(pos, SIDSIZE); // fixed length of characters

        return cookieValue;
    }
    return "";
}

std::string createUserJson(USER user, USERINSTITUTION userInst)
{
    Json::Value jsonValue;
    Json::Value jsonCourseArray;
    Json::Value jsonDegreeArray;

    jsonValue["username"] = user.getUsername();
    jsonValue["avatar"] = user.getAvatar();
    jsonValue["firstname"] = user.getFirstName();
    jsonValue["lastname"] = user.getLastName();
    jsonValue["password"] = user.getLastName();
    jsonValue["rank"] = user.getRank();
    jsonValue["yearStart"] = user.getYearStart();
    jsonValue["yearEnd"] = user.getYearEnd();

    jsonValue["institutionName"] = userInst.institution;

    for (const auto &deg : userInst.degrees)
    {
        Json::Value jsonObject = createDegreeJsonObject(deg);
        jsonDegreeArray.append(jsonObject);
    }

    for (const auto &course : userInst.courses)
    {
        Json::Value jsonObject = createCourseJsonObject(course);
        jsonCourseArray.append(jsonObject);
    }

    jsonValue["courses"] = jsonCourseArray;
    jsonValue["degrees"] = jsonDegreeArray;

    std::cout << "\n\n"
              << jsonValue.toStyledString() << std::endl;
    return jsonValue.toStyledString();
}