#ifndef USER_H
#define USER_H

#include "institution.h"
#include "database.h"

class USER
{
private:
    std::string SID, username, avatar, fName, lName;
    INSTITUTION institution;
    uint16_t yearStart, yearEnd; // 0 to 65,535 (2^16 - 1),
    DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();

public:
    USER(std::string SID, std::string username, std::string avatar, std::string fName, std::string lName,
        INSTITUTION institution, uint16_t yearStart, uint16_t yearEnd)
    {
        this->SID = SID;
        this->username = username;
        this->avatar = avatar;
        this->fName = fName;
        this->lName = lName;
        this->institution = institution;
        this->yearStart = yearStart;
        this->yearEnd = yearEnd;
    }

    USER(USER *user)
    {
        this->SID = user->SID;
        this->username = user->username;
        this->avatar = user->avatar;
        this->fName = user->fName;
        this->lName = user->lName;
        this->institution = user->institution;
        this->yearStart = user->yearStart;
        this->yearEnd = user->yearEnd;
    }

    void setSID(std::string SID)
    {
        this->SID = SID;
    }

    void setUsername(std::string username)
    {
        this->username = username;
    }

    void setAvatar(std::string avatar)
    {
        this->avatar = avatar;
    }

    void setFirstName(std::string fName)
    {
        this->fName = fName;
    }

    void setLastName(std::string lName)
    {
        this->lName = lName;
    }

    void setInstitution(INSTITUTION institution)
    {
        this->institution = institution;
    }

    void setYearStart(uint16_t yearStart)
    {
        this->yearStart = yearStart;
    }

    void setYearEnd(uint16_t yearEnd)
    {
        this->yearEnd = yearEnd;
    }

    std::string getSID()
    {
        return this->SID;
    }

    std::string getUsername()
    {
        return this->username;
    }

    std::string getAvatar()
    {
        return this->avatar;
    }

    std::string getFirstName()
    {
        return this->fName;
    }

    std::string getLastName()
    {
        return this->lName;
    }

    INSTITUTION getInstitution()
    {
        return this->institution;
    }

    uint16_t getYearStart()
    {
        return this->yearStart;
    }

    uint16_t getYearEnd()
    {
        return this->yearEnd;
    }

    bool create(USER *user)
    {
        // dbMan
        // sql::Statement *stmt;
        // sql::PreparedStatement *prep_stmt;
        // sql::ResultSet *res;
        return false;
    }

    USER read()
    {
        return NULL;
    }

    bool update(std::string uid)
    {
        return false;
    }

    bool deleteUser()
    {
        return false;
    }

    std::vector<USER> *selectAll()
    {
        return nullptr;
    }
};

#endif