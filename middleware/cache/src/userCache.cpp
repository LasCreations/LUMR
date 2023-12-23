#include "../lib/userCache.h"

USERCACHE::USERCACHE(){
}

void USERCACHE::preloadUserData(){
    
    this->cacheData = getUsersCacheData();
    
}

void USERCACHE::updateUserData(){

}
        
USER* USERCACHE::getUserFromCache(string key){

    auto data = this->cacheData->find(key);

    if (data != cacheData->end()) {
        // Key found, return the associated user object
        return data->second;
    } else {
        // Key not found, return nullptr or handle as needed
        return nullptr;
    }

}

USER* USERCACHE::getUserFromCache(string username, string password){
    for (const auto& pair : *(this->cacheData)) {
        if(username == pair.second->getUsername() && password == pair.second->getPassword()){
            return pair.second;
        }
    }
    return nullptr;
}


bool USERCACHE::userExists(string username){
    for (const auto& pair : *(this->cacheData)) {
        if(username == pair.second->getUsername()){
            return true;
        }
    }
    return false;
}

void USERCACHE::scan(){
     for (const auto& pair : *(this->cacheData)) {
        cout << "User Data" << std::endl;
        cout << "Key: " << pair.first  << endl; 
        cout << "Username: " << pair.second->getUsername() << std::endl;
        cout << "Password: " << pair.second->getPassword() << std::endl;
        cout << "Token: " << pair.second->getToken() << std::endl;
        cout << "\n" << std::endl;
        cout << "Profile Data" << std::endl;
        cout << "Profile ID: " << pair.second->getProfile()->getProfileID() << std::endl;
        cout << "User ID: " << pair.second->getProfile()->getUserID() << std::endl;
        cout << "Bio: " << pair.second->getProfile()->getBio() << std::endl;
        cout << "Avater URL: " << pair.second->getProfile()->getAvatarURL() << std::endl;
        cout << "Email: " << pair.second->getProfile()->getEmail() << std::endl;
        cout << "Gender: " << pair.second->getProfile()->getGender() << std::endl;
        cout << "Status: " << pair.second->getProfile()->getStatus() << std::endl;
        cout << "\n\n" << std::endl;
    }
}



void USERCACHE::addUserToMap(USER *data){
    (*this->cacheData)[data->getUsername()] = data;
}

bool USERCACHE::isEmpty(){
    if(this->cacheData->empty())
        return true;
    else
        return false;
}