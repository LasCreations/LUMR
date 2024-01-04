#include "userRegistrationController.h"

void handleUserRegistration(CLIENT *client){
    parseUserRegistrationRequest(parseHttpRequest(client->request));
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
    int rank = root["rank"].asInt();
    std::string institutionName = root["institutionName"].asString();

    const Json::Value degreesArray = root["degrees"];
    for (const auto& degree : degreesArray)
        std::cout << "Degree: " << degree.asString() << std::endl;

    std::cout << "Firstname: " << firstname << std::endl;
    std::cout << "Lastname: " << lastname << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Password: " << password << std::endl;
    std::cout << "Avatar: " << avatar << std::endl;
    std::cout << "Rank: " << rank << std::endl;
    std::cout << "InstitutionName: " << institutionName << std::endl;

    return temp;
}