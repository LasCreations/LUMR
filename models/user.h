#ifndef USER_H
#define USER_H

#include "headers.h"
#include "database.h"

class USER
{
private:
    std::string uid, username, avatar, fName, lName, institution;
    std::vector<std::string> courses, degree;
    //let a user have a vector of degrees

    uint16_t yearStart, yearEnd; //0 to 65,535 (2^16 - 1),
    DATABASEMANAGER& dbMan = DATABASEMANAGER::getInstance();

public:
    USER(std::string uid, std::string username, std::string avatar, std::string fName, std::string lName,
         std::string institution, std::vector<std::string> degree, std::vector<std::string> courses, uint16_t yearStart,
         uint16_t yearEnd)
    {
        this->uid = uid;
        this->username = username;
        this->avatar = avatar;
        this->fName = fName;
        this->lName = lName;
        this->institution = institution;
        this->degree = degree;
        this->courses = courses;
        this->yearStart = yearStart;
        this->yearEnd = yearEnd;
    }

    USER(USER *user)
    {
        this->uid = user->uid;
        this->username = user->username;
        this->avatar = user->avatar;
        this->fName = user->fName;
        this->lName = user->lName;
        this->institution = user->institution;
        this->degree = user->degree;
        this->courses = user->courses;
        this->yearStart = user->yearStart;
        this->yearEnd = user->yearEnd;
    }

    void setUID(std::string uid){
        this->uid = uid;
    }

    void setUsername(std::string username){
        this->username = username;
    }

    void setAvatar(std::string avatar){
        this->avatar = avatar;
    }

    void setFirstName(std::string fName){
        this->fName = fName;
    }
        
    void setLastName(std::string lName){
        this->lName = lName;
    }
        
    void setInstitution(std::string institution){
        this->institution = institution;
    }

    void setDegree(std::vector<std::string> degree){
        this->degree = degree;
    }

    void setCourses(std::vector<std::string> courses){
        this->courses = courses;
    }
        
    void setYearStart(uint16_t yearStart){
        this->yearStart = yearStart;
    }

    void setYearEnd(uint16_t yearEnd){
        this->yearEnd = yearEnd;
    }

    std::string getUID (){
        return this->uid;
    }

    std::string getUsername(){
        return this->username;
    }

    std::string getAvatar(){
        return this->avatar;
    }

    std::string getFirstName(){
        return this->fName;
    }
        
    std::string getLastName(){
        return this->lName;
    }
        
    std::string getInstitution(){
        return this->institution;
    }

    std::vector<std::string> getDegree(){
        return this->degree;
    }

    std::vector<std::string> getCourses(){
        return this->courses;
    }
        
    uint16_t getYearStart(){
        return this->yearStart;
    }

    uint16_t getYearEnd(){
        return this->yearEnd;
    }   

    bool create(USER *user){
        // dbMan
        // sql::Statement *stmt;
        // sql::PreparedStatement *prep_stmt;
        // sql::ResultSet *res;
        return false;
    } 

    USER read(){
        return NULL;
    }

    bool update(std::string uid){
        return false;
    }
    
    bool deleteUser(){
        return false;
    }

    std::vector <USER> *selectAll(){
        return nullptr;
    }

};

#endif