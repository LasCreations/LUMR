#ifndef USER_DATA_CACHE_H
#define USER_DATA_CACHE_H

#include "../../include/common.h"


class UserDataCache{

    private:
        std::unordered_map<string, User*> cacheData;
    public:

        UserDataCache();
        void preloadUserData();
        void updateUserData();
        void scan();

        void addUserToMap(User *data);
        bool isEmpty();
        bool userExists(string username, string email);
        User* getUserFromCache(string key);
        User* getUserFromCache(string username, string password);
};

#endif