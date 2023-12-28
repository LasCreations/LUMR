#ifndef CONNECTION_H
#define CONNECTION_H

#include "user.h"

class CONNECTION{
    private:
        USER* user1;
        USER* user2;
        bool user1_status;
        bool user2_status;
        
    public:
        CONNECTION(){
            this->user1 = new USER();
            this->user2 = new USER();
            this->user1_status = true;
            this->user2_status = false;
        }

        CONNECTION(USER* user1, USER* user2, bool user1_status, bool user2_status){
            this->user1 = user1;
            this->user2 = user2;
            this->user1_status = user1_status;
            this->user2_status = user2_status;
        }

        void setUser1(USER* user1){
            this->user1 = user1;
        }

        void setUser2(USER* user2){
            this->user2 = user2;
        }

        void setUser1Status(bool user1_status){
            this->user1_status = user1_status;
        }

        void setUser2Status(bool user2_status){
            this->user2_status = user2_status;
        }
        
        USER *getUser1(){
            return this->user1;
        }

        USER *getUser2(){
            return this->user2;
        }

        bool getUser1Status(){
            return this->user1_status;
        }

        bool getUser2Status(){
            return this->user2_status;
        }
};


#endif