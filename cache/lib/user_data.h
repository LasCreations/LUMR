#ifndef USER_DATA_CACHE_H
#define USER_DATA_CACHE_H

#include "../../include/common.h"


class UserDataCache{

    private:
        std::unordered_map<string, User*> cacheData;
        string test;
    public:

        UserDataCache();
        void preloadUserData();
        void updateUserData();
        void scan();

        User* getUserFromCache(string key);
        string getTest();
};

#endif