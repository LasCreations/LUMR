#ifndef USER_CACHE_H
#define USER_CACHE_H

#include "../../../utils/common.h"
#include "../../../database/queries/lib/userQueries.h"

class USERCACHE{

    private:
        std::unordered_map<string, USER*> *cacheData;
    public:

        USERCACHE();
        void preloadUserData(DATABASEMANAGER *dbMan);
        void updateUserData();
        void scan();
        void addUserToMap(USER *data);
        void updateUserTokenInCache(USER *data, string token);
        bool isEmpty();
        bool userExists(string username);
        USER* updateUserProfileInCache(PROFILE *data);
        USER* getUserFromCache(string key);
        USER* getUserFromCache(string username, string password);
        USER* getUserFromCacheByToken(string token);
};

#endif