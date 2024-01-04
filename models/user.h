#ifndef USER_H
#define USER_H

#include "institution.h"
#include "database.h"

class USER
{
private:
    std::string SID, username, password, avatar, fName, lName;
    INSTITUTION institution;
    uint16_t yearStart, yearEnd, rank;

public:
    USER(std::string SID, std::string username, std::string password, std::string avatar, std::string fName, std::string lName,
        INSTITUTION institution, uint16_t yearStart, uint16_t yearEnd, uint16_t rank)
    {
        this->SID = SID;
        this->password = password;
        this->username = username;
        this->avatar = avatar;
        this->fName = fName;
        this->lName = lName;
        this->institution = institution;
        this->yearStart = yearStart;
        this->yearEnd = yearEnd;
        this->rank = rank;
    }

    USER(USER *user)
    {
        this->SID = user->SID;
        this->username = user->username;
        this->password = user->password;
        this->avatar = user->avatar;
        this->fName = user->fName;
        this->lName = user->lName;
        this->institution = user->institution;
        this->yearStart = user->yearStart;
        this->yearEnd = user->yearEnd;
        this->rank = user->rank;
    }

    void setSID(std::string SID)
    {
        this->SID = SID;
    }

    void setUsername(std::string username)
    {
        this->username = username;
    }

    void setPassword(std::string password)
    {
        this->password = password;
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

    void setRank(uint16_t rank)
    {
        this->rank = rank;
    }

    std::string getSID()
    {
        return this->SID;
    }

    std::string getUsername()
    {
        return this->username;
    }

    std::string getPassword()
    {
        return this->password;
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

    uint16_t getRank()
    {
        return this->rank;
    }

    bool create(USER *user)
    {
        // DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();
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