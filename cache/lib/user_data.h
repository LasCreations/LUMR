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

        bool isEmpty();
        User* getUserFromCache(string key);
};

#endif