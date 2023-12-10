#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User{
    private:
        string username, email, password;
    public:
        User(){
            this->email = "";
            this->username = "";
            this->password = "";
        }

        User(string username, string email, string password){
            this->email = email;
            this->username = username;
            this->password = password;
        }

        User(User *user){
            this->email = user->email;
            this->username = user->username;
            this->password = user->password;
        }

        void setUsername(string username){
            this->username = username;
        }

        void setEmail(string email){
            this->email = email;
        }

        void setPassword(string password){
            this->password = password;
        }

        string getUsername(){
            return this->username;
        }

        string getPassword(){
            return this->password;
        }

        string getEmail(){
            return this->email;
        }
};

#endif