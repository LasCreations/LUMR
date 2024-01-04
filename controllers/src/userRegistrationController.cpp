#include "userRegistrationController.h"

void handleUserRegistration(CLIENT *client){
    parseUserRegistrationRequest(parseHttpRequest(client->request));
    std::string httpResponse = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
    send(client->socket, httpResponse.c_str(), httpResponse.length(), 0);

}

USER parseUserRegistrationRequest(std::string jsonData){

    USER temp = new USER();

    Json::CharReaderBuilder readerBuilder;
    Json::Value root;

    std::istringstream jsonStream(jsonData);
    Json::parseFromStream(readerBuilder, jsonStream, &root, nullptr);

    std::string firstname = root["firstname"].asString();
    std::string lastname = root["lastname"].asString();
    std::string username = root["username"].asString();
    std::string password = root["password"].asString();
    std::string avatar = root["avatar"].asString();
    std::string institutionName = root["institutionName"].asString();
    //convert string to int then to uint16_t
    uint16_t rank =  static_cast<uint16_t>(std::stoi(root["rank"].asString()));
    uint16_t yearStart = static_cast<uint16_t>(std::stoi(root["yearStart"].asString()));
    uint16_t yearEnd = static_cast<uint16_t>(std::stoi(root["yearEnd"].asString()));

    std::cout << "Firstname: " << firstname << std::endl;
    std::cout << "Lastname: " << lastname << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Avatar: " << avatar << std::endl;
    std::cout << "Rank: " << rank << std::endl;
    std::cout << "InstitutionName: " << institutionName << std::endl;
    std::cout << "Year Start: " << yearStart << std::endl;
    std::cout << "Year End: " << yearEnd << std::endl;

    const Json::Value degreesArray = root["degrees"];
    for (const auto& degree : degreesArray)
        std::cout << "Degree: " << degree.asString() << std::endl;

    const Json::Value coursesArray = root["courses"];
    for (const auto& course : coursesArray)
        std::cout << "Courses: " << course.asString() << std::endl;

    return temp;
}