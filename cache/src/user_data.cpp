#include "../lib/user_data.h"

UserDataCache::UserDataCache(){
}

void UserDataCache::preloadUserData(){
    
    if (dbConn->createConnection())
    {
        this->cacheData = *(dbConn->getUsersCacheData());
    }
    
}

void UserDataCache::updateUserData(){

}
        
User* UserDataCache::getUserFromCache(string key){

    auto data = this->cacheData.find(key);

    if (data != cacheData.end()) {
        // Key found, return the associated user object
        return data->second;
    } else {
        // Key not found, return nullptr or handle as needed
        return nullptr;
    }

}

User* UserDataCache::getUserFromCache(string username, string password){
    for (const auto& pair : this->cacheData) {
        if(username == pair.second->getUsername() && password == pair.second->getPassword()){
            return pair.second;
        }
    }
    return nullptr;
}


bool UserDataCache::userExists(string username, string email){
    for (const auto& pair : this->cacheData) {
        if(username == pair.second->getUsername() && email == pair.second->getEmail()){
            return true;
        }
    }
    return false;
}

void UserDataCache::scan(){
    //  for (const auto& pair : this->cacheData) {
        // cout << "Key: " << pair.first  << endl; 
        // cout << "Username: " << pair.second->getUsername() << std::endl;
        // cout << "Email: " << pair.second->getEmail() << std::endl;
        // cout << "Avatar: " << pair.second->getAvatarURL() << std::endl;
        // cout << "Password: " << pair.second->getPassword() << std::endl;
        // cout << "Passport: " << pair.second->getCookie() << std::endl;
        // cout << "\n\n" << std::endl;
    // }
}



void UserDataCache::addUserToMap(User *data){
    this->cacheData[data->getCookie()] = data;
}

bool UserDataCache::isEmpty(){
    if(this->cacheData.empty())
        return true;
    else
        return false;
}
