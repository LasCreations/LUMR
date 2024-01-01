#ifndef CACHE_H
#define CACHE_H

#include "common.h"
#include "user.h"

//Using a singleton approach for caching system
class CACHE{

    private:
        CACHE();
        std::unordered_map<std::string, USER> userMap;

    public:
        static CACHE& getInstance();
        std::unordered_map<std::string, USER>& getUserMap();
        // void setUserData(int key, const std::string& value);
};

#endif