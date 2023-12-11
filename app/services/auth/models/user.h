#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User
{
private:
    string username, email, password, cookie;

public:
    User()
    {
        this->email = "";
        this->username = "";
        this->password = "";
        this->cookie = "";
    }

    User(string username, string email, string password, string cookie)
    {
        this->email = email;
        this->username = username;
        this->password = password;
        this->cookie = cookie;
    }

    User(User *user)
    {
        this->email = user->email;
        this->username = user->username;
        this->password = user->password;
        this->cookie = user->cookie;
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

    string getUsername()
    {
        return this->username;
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