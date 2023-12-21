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

    User *data = nullptr;

    return data;

}

void UserDataCache::scan(){
     for (const auto& pair : this->cacheData) {
        cout << "Key: " << pair.first  << endl; 
        cout << "Username: " << pair.second->getUsername() << std::endl;
        cout << "Email: " << pair.second->getEmail() << std::endl;
        cout << "Avatar: " << pair.second->getAvatarURL() << std::endl;
        cout << "Password: " << pair.second->getPassword() << std::endl;
        cout << "Passport: " << pair.second->getCookie() << std::endl;
        cout << "\n\n" << std::endl;
    }
}
