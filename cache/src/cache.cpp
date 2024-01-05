#include "cache.h"

CACHE::CACHE(){
    USER temp;
    this->institutionMap = INSTITUTION().getAll();
    this->userMap = temp.getAll();
    this->sessionIDMap = temp.getAllSession();
}

CACHE& CACHE::getInstance(){
    static CACHE instance;
    return instance;
}

std::unordered_map<std::string, USER>& CACHE::getUserMap() {
    return this->userMap;
}

std::unordered_map<std::string, INSTITUTION>& CACHE::getInstitutionMap(){
    return this->institutionMap;
}

std::unordered_map<std::string, USER> &CACHE::getSessionIDMap(){
    this->sessionIDMap;
}

void CACHE::insertUserToMap(USER user){
    this->userMap[user.getUsername()] = user;
}

void CACHE::insertUserSessionToMap(USER user){
    this->sessionIDMap[user.getSID()] = user;
}