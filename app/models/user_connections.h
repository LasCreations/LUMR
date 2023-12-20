#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include "user.h"

class Connections{
    private:
        User* user1;
        User* user2;
        bool user1_status, user2_status;
        
    public:
        Connections(){
            this->user1 = new User();
            this->user2 = new User();
            this->user1_status = false;
            this->user2_status = false;
        }

        Connections(User* user1, User* user2, bool user1_status, bool user2_status){
            this->user1 = user1;
            this->user2 = user2;
            this->user1_status = user1_status;
            this->user2_status = user2_status;
        }

        void setUser1(User* user1){
            this->user1 = user1;
        }

        void setUser1(User* user2){
            this->user2 = user2;
        }

        void setUser1_status(bool user1_status){
            this->user1_status = user1_status;
        }

        void setUser2_status(bool user2_status){
            this->user2_status = user2_status;
        }
        
        User *getUser1(){
            return this->user1;
        }

        User *getUser2(){
            return this->user2;
        }

        bool getUser1_Status(){
            this->user1_status;
        }
};


#endif