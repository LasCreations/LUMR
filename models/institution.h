#ifndef INSTITUTION_H
#define INSTITUTION_H

#include "degree.h"

class INSTITUTION{
    private:
        std::vector<DEGREE> *degrees;
        std::string name;
    public:
        INSTITUTION(){
            this->name = "";
            this->degrees = nullptr;
        }

        INSTITUTION(std::string name, std::vector<DEGREE> *degrees){
            this->name = name;
            this->degrees = degrees;
        }

        INSTITUTION(INSTITUTION *institution){
            this->name = institution->name;
            this->degrees = institution->degrees;
        }

        void setInstitutionName(std::string name){
            this->name = name;
        }

        void setInstitutionDegrees(std::vector<DEGREE> *degrees){
            this->degrees = degrees;
        }

        std::string getInstitutionName(){
            return this->name;
        }

        std::vector<DEGREE> *getInstitutionDegrees(){
            return this->degrees;
        }
};

#endif