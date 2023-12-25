#ifndef CONNECTION_H
#define CONNECTION_H

#include "user.h"

class CONNECTION{
    private:
        USER* user1;
        USER* user2;
        bool status;
        
    public:
        CONNECTION(){
            this->user1 = new USER();
            this->user2 = new USER();
            this->status = false;
        }

        CONNECTION(USER* user1, USER* user2, bool status){
            this->user1 = user1;
            this->user2 = user2;
            this->status = status;
        }

        void setUser1(USER* user1){
            this->user1 = user1;
        }

        void setUser2(USER* user2){
            this->user2 = user2;
        }

        void setStatus(bool status){
            this->status = status;
        }
        
        USER *getUser1(){
            return this->user1;
        }

        USER *getUser2(){
            return this->user2;
        }

        bool getStatus(){
            return this->status;
        }
};


#endif