#ifndef COURSE_H
#define COURSE_H

#include "common.h"
#include "database.h"

class COURSE
{
private:
    std::string code, name;

public:
    COURSE()
    {
        this->code = "";
        this->name = "";
    }

    COURSE(std::string code, std::string name)
    {
        this->code = code;
        this->name = name;
    }

    COURSE(COURSE *course)
    {
        this->code = course->code;
        this->name = course->name;
    }

    void setCourseCode(std::string code)
    {
        this->code = code;
    }

    void setCourseName(std::string name)
    {
        this->name = name;
    }

    std::string  getCourseCode() const
    {
        return this->code;
    }

    std::string  getCourseName() const
    {
        return this->name;
    }

    std::vector<COURSE> *getAll(std::string degreeCode)
    {
        std::vector<COURSE> *data = nullptr;
        sql::Statement *stmt = nullptr;
        sql::ResultSet *res = nullptr;

        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();

        try
        {
            data = new std::vector<COURSE>;
            std::string sql = "SELECT course.name, course.code FROM degree_courses "
                                     "JOIN course ON degree_courses.course_code = course.code "
                                     "WHERE degree_courses.degree_code = ?";

            sql::PreparedStatement *pstmt = dbMan.getConnection()->prepareStatement(sql);
            pstmt->setString(1, degreeCode);

            res = pstmt->executeQuery();

            while (res->next())
            {
                // std::cout << res->getString("name") << std::endl;
                // std::cout << res->getString("code") << std::endl;
                data->push_back(COURSE(res->getString("code"), res->getString("name")));
            }

            // Clean up prepared statement
            delete pstmt;
        }
        catch (const sql::SQLException &e)
        {
            std::cerr << "SQLException: " << e.what() << std::endl;
        }

        // Clean up
        delete stmt;
        delete res;

        return data;
    }
};

#endif