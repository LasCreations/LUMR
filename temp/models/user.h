#ifndef USER_H
#define USER_H

#include "profile.h"

using namespace std;

class USER
{
private:
    string username, password, token;
    PROFILE *profile;

public:
    USER()
    {
        this->token = "";
        this->username = "";
        this->password = "";
        this->profile = new PROFILE();
    }

    USER(string username, string password, string token, PROFILE *profile)
    {
        this->profile = profile;
        this->username = username;
        this->password = password;
        this->token = token;
    }

    USER(USER *user)
    {
        this->profile = user->profile;
        this->username = user->username;
        this->password = user->password;
        this->token = user->token;
    }

    void setProfile(PROFILE *profile){
        this->profile = profile;
    }

    void setUsername(string username)
    {
        this->username = username;
    }

    void setPassword(string password)
    {
        this->password = password;
    }

    void setToken(string token)
    {
        this->token = token;
    }

    PROFILE *getProfile(){
        return this->profile;
    }

    string getUsername()
    {
        return this->username;
    }

    string getPassword()
    {
        return this->password;
    }

    string getToken()
    {
        return this->token;
    }
};

#endif