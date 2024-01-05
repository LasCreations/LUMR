#include "cache.h"

CACHE::CACHE(){
    this->institutionMap = INSTITUTION().getAll();
    this->userMap = USER().getAll();
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

void CACHE::insertUserToMap(USER user){
    this->userMap[user.getUsername()] = user;
}
// void CACHE::setUserData(int key, const std::string& value) {
//     this->userMap[key] = value;
// }