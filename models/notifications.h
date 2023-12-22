#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include "../include/common.h"

class Notification
{

private:
    string notificationID, username, senderID, type, content;
    bool status;
    time_t timestamp;

public:
    Notification()
    {
    }
    Notification(string notificationID, string username, string senderID, string type, string content, bool status, time_t timestamp)
    {
        this->notificationID = notificationID;
        this->username = username;
        this->senderID = senderID;
        this->type = type;
        this->content = content;
        this->status = status;
        this->timestamp = timestamp;
    }
    void setNotificationID(string notificationID)
    {
        this->notificationID = notificationID;
    }
    void setUsername(string username)
    {
        this->username = username;
    }
    void setType(string type)
    {
        this->type = type;
    }
    void setContent(string content)
    {
        this->content = content;
    }
    void setSenderID(string senderID)
    {
        this->senderID = senderID;
    }
    void setStatus(bool status)
    {
        this->status = status;
    }
    void setTimeStamp(time_t timestamp)
    {
        this->timestamp = timestamp;
    }
    string getNotificationID()
    {
        return this->notificationID;
    }
    string getUsername(){
        return this->username;
    }
    string getType(){
        return this->type;
    }
    string getContent(){
        return this->content;
    }
    string getSenderID(){
        return this->senderID;
    }
    bool getStatus(){
        return this->status;
    }
    time_t getTimeStamp(){
        return this->timestamp;
    }
};

#endif