#ifndef SCHEDULE_H_INCLUDED
#define SCHEDULE_H_INCLUDED

#include <iostream>
#include <list>
#include <vector>

#include "Course.h"

constexpr const int CREDIT_LIMIT = 12;

/**
 *
 */
class Schedule {
    public:
        /**
         * Aliases for the different possible containers
         * <p>
         * After your code is working, switch between them.
         * You should have identical results for all of them.
         */
        //using CourseCollection = std::list<Course>;
        using CourseCollection = std::vector<Course>;

        using iterator       = CourseCollection::iterator;
        using const_iterator = CourseCollection::const_iterator;

    private:
        /**
         * All courses in _this_ schedule.
         */
        CourseCollection allCourses;

        /**
         * Add a course the the schedule. This is a standard 
         * linked list append.
         *
         * @pre (!wouldViolateCreditLimit && notAlreadyInSchedule)
         */
        void appendNoCheck(Course course);

    public:
        /**
         * Construct an empty schedule
         */
        Schedule();

        /**
         * Retrieve the total number of credits
         */
        int getCredits() const;

        /**
         * Attempt to add a course AND
         * perform all validation checks by calling:
         *   - wouldViolateCreditLimit
         *   - alreadyInSchedule
         *   - appendNoCheck
         */
        bool add(Course course);

        /**
         * Check if adding this course would violate
         * the CREDIT_LIMIT. This is an evaluation of
         * (toAdd.getCredits() + this->totalCredits) > CREDIT_LIMIT
         *
         * @returns false if adding the course
         *    would not violate the CREDIT_LIMIT
         */
        bool wouldViolateCreditLimit(Course course) const;

        /**
         * Check if a course with the same number is already
         * present in the schedule.
         *
         * @returns true if while traversing the collection
         *   of courses, a course with the same course number
         *   was found 
         */
        bool alreadyInSchedule(Course course) const;

        /**
         * Display a listing of each course and
         * the total number of credit hours
         */
        void display(std::ostream& outs) const;

        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        /**
         * Return the number of courses in the schedule
         */
        size_t size() const;
};

/**
 *
 */
inline
bool Schedule::add(Course course)
{
    if (wouldViolateCreditLimit(course)) {
        return false;
    }

    if (alreadyInSchedule(course)) {
        return false;
    }

    // Success - all checks passed
    appendNoCheck(course);
    return true;
}

//-----------------------------------------------------------------------------
inline
Schedule::iterator Schedule::begin()
{
    return allCourses.begin();
}

//-----------------------------------------------------------------------------
inline
Schedule::iterator Schedule::end()
{
    return allCourses.end();
}

//-----------------------------------------------------------------------------
inline
Schedule::const_iterator Schedule::begin() const
{
    return allCourses.begin();
}

//-----------------------------------------------------------------------------
inline
Schedule::const_iterator Schedule::end() const
{
    return allCourses.end();
}

inline
size_t Schedule::size() const
{
    return allCourses.size();
}

/**
 * Print the Schedule through use of the display member function
 */
inline 
std::ostream& operator<<(std::ostream &outs, const Schedule &prt)
{
    prt.display(outs);
    
    return outs;
}
#endif