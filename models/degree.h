#ifndef DEGREE_H
#define DEGREE_H

#include "course.h"
#include "database.h"

class DEGREE
{
private:
    std::string name, code;
    std::unordered_map<std::string, COURSE> courses;

public:
    DEGREE()
    {}

    DEGREE(std::string name, std::string code, std::unordered_map<std::string, COURSE>courses)
    {
        this->name = name;
        this->code = code;
        this->courses = courses;
    }

    DEGREE(DEGREE *degree)
    {
        this->name = degree->name;
        this->code = degree->code;
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

    void setCourses(std::unordered_map<std::string, COURSE> courses)
    {
        this->courses = courses;
    }

    std::string getDegreeName() const
    {
        return this->name;
    }

    std::string getDegreeCode() const
    {
        return this->code;
    }

    std::unordered_map<std::string, COURSE> getCourses() const 
    {
        return this->courses;
    }

    std::unordered_map<std::string, DEGREE> getAll(std::string institutionCode)
    {
        std::unordered_map<std::string, DEGREE> data;
        sql::Statement *stmt = nullptr;
        sql::ResultSet *res = nullptr;

        DATABASEMANAGER &dbMan = DATABASEMANAGER::getInstance();

        try
        {
            std::string degree_sql = "SELECT degrees.name, degrees.code FROM institutions_degree "
                                     "JOIN degrees ON institutions_degree.degree_code = degrees.code "
                                     "WHERE institutions_degree.institution_code = ?";

            sql::PreparedStatement *pstmt = dbMan.getConnection()->prepareStatement(degree_sql);
            pstmt->setString(1, institutionCode);

            // Execute the query
            res = pstmt->executeQuery();

            while (res->next())
            {
                data[res->getString("name")] = DEGREE(res->getString("name"), res->getString("code"), COURSE().getAll(res->getString("code")));
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