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
        std::unordered_map<std::string, USER> sessionIDMap;
        std::unordered_map<std::string, USERINSTITUTION>  userInstitutionMap;
        //UserInstitutionMap
    public:
        static CACHE& getInstance();
        std::unordered_map<std::string, USER>& getUserMap();
        std::unordered_map<std::string, INSTITUTION>& getInstitutionMap();
        std::unordered_map<std::string, USER> &getSessionIDMap();
        void insertUserToMap(USER user);
        void insertUserSessionToMap(USER user);
        
};

#endif