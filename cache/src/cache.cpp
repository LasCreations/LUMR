#include "cache.h"

CACHE::CACHE(){

}

CACHE& CACHE::getInstance(){
    static CACHE instance;
    return instance;
}

std::unordered_map<std::string, USER>& CACHE::getUserMap() {
    return this->userMap;
}

// void CACHE::setUserData(int key, const std::string& value) {
//     this->userMap[key] = value;
// }