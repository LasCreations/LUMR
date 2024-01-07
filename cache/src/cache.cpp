#include "cache.h"

CACHE::CACHE()
{
    USER temp;
    this->institutionMap = INSTITUTION().getAll();
    this->userMap = temp.getAll();
    this->sessionIDMap = temp.createSessionMap(this->userMap);
    this->userInstitutionMap = temp.createUserInstitutionMap(this->userMap);
}

CACHE &CACHE::getInstance()
{
    static CACHE instance;
    return instance;
}

std::unordered_map<std::string, USER> &CACHE::getUserMap()
{
    return this->userMap;
}

std::unordered_map<std::string, INSTITUTION> &CACHE::getInstitutionMap()
{
    return this->institutionMap;
}

std::unordered_map<std::string, USER> &CACHE::getSessionIDMap()
{
    return this->sessionIDMap;
}

std::unordered_map<std::string, USERINSTITUTION> &CACHE::getUserInstitutionMap(){
    return this->userInstitutionMap;
}

void CACHE::insertUserToMap(USER user)
{
    this->userMap[user.getUsername()] = user;
}

void CACHE::insertUserSessionToMap(USER user)
{
    this->sessionIDMap[user.getSID()] = user;
}

void CACHE::insertUserInstitutionToMap(USERINSTITUTION userInst){
    this->userInstitutionMap[userInst.username] = userInst;
}