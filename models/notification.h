#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include"../utils/common.h"

class NOTIFICATION{
    private:
        string notification_id,	reciever_id, sender_id, type, content;
        bool status;
        time_t timestamp;

    public:
        NOTIFICATION(){
            this->notification_id = "";
            this->reciever_id = "";
            this->sender_id = "";
            this->type = "";
            this->content = "";
            this->status = false;
            this->timestamp = time(0); //set it as the current time
        }

        NOTIFICATION(string notification_id, string reciever_id, string sender_id, string type,
                        string content, bool status, time_t timestamp){
            this->notification_id = notification_id;
            this->reciever_id = reciever_id;
            this->sender_id = sender_id;
            this->type = type;
            this->content = content;
            this->status = status;
            this->timestamp = timestamp;
        }

        NOTIFICATION(NOTIFICATION *notification){
            this->notification_id = notification->notification_id;
            this->reciever_id = notification->reciever_id;
            this->sender_id = notification->sender_id;
            this->type = notification->type;
            this->content = notification->content;
            this->status = notification->status;
            this->timestamp = notification->timestamp;
        }

        void setNotificationID(string notification_id){
            this->notification_id = notification_id;
        }

        void setRecieverID(string reciever_id){
            this->reciever_id = reciever_id;
        }

        void setSenderID(string sender_id){
            this->sender_id = sender_id;
        }

        void setType(string type){
            this->type = type;
        }

        void setContent(string content){
            this->content = content;
        }

        void setStatus(bool status){
            this->status = status;
        }

        void setTimestamp(time_t timestamp){
            this->timestamp = timestamp;
        }

        string getNotificationID(){
            return this->notification_id;
        }

        string getRecieverID(){
            return this->reciever_id;
        }

        string getSenderID(){
            return this->sender_id;
        }

        string getType(){
            return this->type;
        }

        string getContent(){
            return this->content = content;
        }

        bool getStatus(){
            return this->status;
        }

        time_t getTimestamp(){
            return this->timestamp;
        }

};

#endif
