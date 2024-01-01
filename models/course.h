#ifndef COURSE_H
#define COURSE_H

#include "headers.h"

class COURSE
{
private:
    std::string code, name;
    bool completed, current;

public:
    COURSE()
    {
        this->code = "";
        this->name = "";
        this->completed = false;
        this->current = false;
    }

    COURSE(std::string code, std::string name, bool completed, bool current)
    {
        this->code = code;
        this->name = name;
        this->completed = completed;
        this->current = current;
    }

    COURSE(COURSE *course)
    {
        this->code = course->code;
        this->name = course->name;
        this->completed = course->completed;
        this->current = course->current;
    }

    void setCourseCode(std::string code)
    {
        this->code = code;
    }

    void setCourseName(std::string name)
    {
        this->name = name;
    }

    void setCompletedStatus(bool completed)
    {
        this->completed = completed;
    }

    void setCurrentStatus(bool current){
        this->current = current;
    }

    std::string  getCourseCode()
    {
        return this->code;
    }

    std::string  getCourseName()
    {
        return this->name;
    }

    bool getCompletedStatus()
    {
        return this->completed;
    }

    bool getCurrentStatus(){
        return this->current;
    }
};

#endif