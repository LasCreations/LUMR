#ifndef DEGREE_H
#define DEGREE_H

#include "course.h"

class DEGREE
{
private:
    std::string name, code;
    std::vector<COURSE> *courses;
    bool completed, current;

public:
    DEGREE()
    {
        this->name = "";
        this->code = "";
        this->completed = false;
        this->current = false;
        this->courses = nullptr;
    }

    DEGREE(std::string name, std::string code, bool completed, bool current, std::vector<COURSE> *courses)
    {
        this->name = name;
        this->code = code;
        this->completed = completed;
        this->current = current;
        this->courses = courses;
    }

    DEGREE(DEGREE *degree)
    {
        this->name = degree->name;
        this->code = degree->code;
        this->completed = degree->completed;
        this->current = degree->current;
        this->courses = degree->courses;
    }

    void setDegreeName(std::string name)
    {
        this->name = name;
    }

    void setDegreeCode(std::string code)
    {
        this->code = code;
    }

    void setCompletedStatus(bool completed)
    {
        this->completed = completed;
    }

    void setCurrentStatus(bool current)
    {
        this->current = current;
    }

    void setCourses(std::vector<COURSE> *courses){
        this->courses = courses;
    }

    std::string getDegreeName()
    {
        return this->name;
    }

    std::string getDegreeCode()
    {
        return this->code;
    }

    bool getCompletedStatus()
    {
        return this->completed;
    }

    bool getCurrentStatus()
    {
        return this->current;
    }

    std::vector<COURSE> *getCourses(){
        return this->courses;
    }
};

#endif