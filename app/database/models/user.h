#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
private:
    string username, email, password, cookie, avatarURL;

public:
    User()
    {
        this->email = "";
        this->username = "";
        this->password = "";
        this->cookie = "";
        this->avatarURL = "";
    }

    User(string username, string email, string password, string cookie, string avatarURL)
    {
        this->email = email;
        this->username = username;
        this->password = password;
        this->cookie = cookie;
        this->avatarURL = avatarURL;
    }

    User(User *user)
    {
        this->email = user->email;
        this->username = user->username;
        this->password = user->password;
        this->cookie = user->cookie;
        this->avatarURL = user->avatarURL;
    }

    void setUsername(string username)
    {
        this->username = username;
    }

    void setEmail(string email)
    {
        this->email = email;
    }

    void setPassword(string password)
    {
        this->password = password;
    }

    void setCookie(string cookie)
    {
        this->cookie = cookie;
    }

    void setAvatarURL(string avatarURL)
    {
        this->avatarURL = avatarURL;
    }

    string getUsername()
    {
        return this->username;
    }

    string getAvatarURL()
    {
        return this->avatarURL;
    }

    string getPassword()
    {
        return this->password;
    }

    string getEmail()
    {
        return this->email;
    }

    string getCookie()
    {
        return this->cookie;
    }
};

#endif