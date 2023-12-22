#ifndef PROFILE_H
#define PROFILE_H

#include"../utils/common.h"

class PROFILE{

    private:
        string profile_id, user_id, email, avatar_url, bio, gender;
	    bool status;

    public:
        PROFILE(){
            this->profile_id = "";
            this->user_id = "";
            this->email  = "";
            this->avatar_url  = "";
            this->bio = "";
            this->gender = "";
	        this->status = true; //user currently online
        }

        PROFILE(PROFILE *profile){
            this->profile_id = profile->profile_id;
            this->user_id = profile->user_id;
            this->email  = profile->email;
            this->avatar_url  = profile->avatar_url;
            this->bio = profile->bio;
            this->gender = profile->gender;
	        this->status = profile->status;
        }

        PROFILE(string profile_id, string user_id, string email, string avatar_url,string bio,string gender,bool status ){
            this->profile_id = profile_id;
            this->user_id = user_id;
            this->email  = email;
            this->avatar_url  = avatar_url;
            this->bio = bio;
            this->gender = gender;
	        this->status = status;
        }

        void setProfileID(string profile_id){
            this->profile_id = profile_id;
        }

        void setUserID(string user_id){
            this->user_id = user_id;
        }

        void setEmail(string email){
            this->email  = email;
        }

        void setAvatarURL(string avatar_url){
            this->avatar_url  = avatar_url;
        }

        void setBio(string bio){
            this->bio = bio;
        }

        void setGender(string gender){
            this->gender = gender;
        }

        void setStatus(bool status){
            this->status = status;
        }

        string getProfileID(){
            return this->profile_id;
        }

        string getUserID(){
            return this->user_id;
        }

        string getEmail(){
            return this->email;
        }

        string getAvatarURL(){
            return this->avatar_url;
        }

        string getBio(){
            return this->bio;
        }

        string getGender(){
            return this->gender;
        }

        bool getStatus(){
            return this->status;
        }

};
#endif