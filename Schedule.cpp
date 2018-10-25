#include <utility>
#include <algorithm>
#include <numeric>

#include "Schedule.h"

using namespace std::rel_ops;

//------------------------------------------------------------------------------
/**
 * @todo accept that this function is already 100% complete as provided
 */
Schedule::Schedule()
{
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
int Schedule::getCredits() const
{
    // @todo remove the next line and complete this function.
    int credits = 0;

    std::vector<Course>::const_iterator it;

    for(it = allCourses.begin(); it!= allCourses.end(); it++)
    {
        credits += it->getCredits();
    }
    return credits;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
void Schedule::appendNoCheck(Course course)
{
    // use the std::{vector,list} push_back function.
    allCourses.push_back(course);

}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
bool Schedule::wouldViolateCreditLimit(Course course) const
{
    // @todo remove the next line and complete this function.


    std::vector<Course>::const_iterator it;

    for(it = allCourses.begin(); it!= allCourses.end(); it++)
    {

        if(course.getCredits() + getCredits() > CREDIT_LIMIT)
        {
            return true;
        }

    }

    return false;
}

//------------------------------------------------------------------------------
bool Schedule::alreadyInSchedule(Course course) const
{
    // @todo remove the next line and complete this function.
    std::vector<Course>::const_iterator it;

    for(it = allCourses.begin(); it!= allCourses.end(); it++)
    {
        if(it->getNumber() == course.getNumber())
        {
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
/**
 * @todo implement this function
 */
void Schedule::display(std::ostream& outs) const
{
    outs << "  (" << getCredits() << " Total Credits)" << "\n";

    // @todo Add the missing output loop to complete this function.

    std::vector<Course>::const_iterator it = allCourses.begin();

    while(it != allCourses.end())
    {
        outs << "  - " << *(it) << "\n";

        it++;
    }


}
