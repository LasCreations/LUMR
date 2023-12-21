#ifndef USER_DATA_CACHE_H
#define USER_DATA_CACHE_H

#include "../../api/lib/common.h"


#include <unordered_map>

class UserDataCache{

    private:
        unordered_map<string,User*> cacheData;
    public:

        void preloadUserData();
        void updateUserData();
        User* getUserFromCache(string key);
};

#endif