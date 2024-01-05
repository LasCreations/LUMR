#ifndef COURSE_CONTROLLER_H
#define COURSE_CONTROLLER_H

#include "cache.h"

struct COURSEREQUEST{
    std::string degree, institution;
};

void handleCourses(CLIENT *client);
COURSEREQUEST parseCourseRequest(std::string request);
std::string createCoursesJsonArray(std::unordered_map<std::string, COURSE> courses);
Json::Value createCourseJsonObject(std::string name);

#endif