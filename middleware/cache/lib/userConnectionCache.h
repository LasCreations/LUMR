#ifndef USER_CONNECTION_CACHE_H
#define USER_CONNECTION_CACHE_H


#include "../../../database/queries/lib/userConnectionQueries.h"


class USERCONNECTIONCACHE{
    private:
        std::unordered_map<string, CONNECTION*> *cacheConnectionData;

    public:
};


#endif