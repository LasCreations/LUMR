#ifndef CACHE_H
#define CACHE_H

#include "common.h"
#include "user.h"
#include "institution.h"

//Using a singleton approach for caching system
class CACHE{

    private:
        CACHE();
        std::unordered_map<std::string, USER> userMap;
        std::unordered_map<std::string, INSTITUTION> institutionMap;
        //UserInstitutionMap
    public:
        static CACHE& getInstance();
        std::unordered_map<std::string, USER>& getUserMap();
        void insertUserToMap(USER user);
        std::unordered_map<std::string, INSTITUTION>& getInstitutionMap();
};

#endif