#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iterator>

#include "Course.h"
#include "Student.h"

using namespace std;

using StudentList = vector<Student>;

/**
 * Trim leading and trailing whitespace from a string.
 * 
 * @param str string to prune
 * 
 * @pre str is nonempty
 */
void trim(string& str);

/**
 * Print the Student through use of the display member function
 */
std::istream& operator>>(std::istream &ins, Student& rd);

/**
 * Parse a list of student names
 *
 * @return list of Student objects
 */
StudentList readStudentList(std::istream& ins);

/**
 * Process an enrollment requests file. For each request,
 * lookup the student and attempt to add a selected course
 * to hist/her schedule.
 */
void processEnrollmentRequests(std::istream& ins, StudentList& students);

/**
 * Print the names of all students
 */
void printStudentNames(std::ostream& outs, const StudentList& students);

/**
 * Print each student along with his/her full schedule
 */
void printStudentSchedules(std::ostream& outs, const StudentList& students);

/**
 * Assignment 1: Course Registration
 *
 * @param argv[1] Student List filename
 * @param argv[2] Enrollment Requests filename
 */
int main(int argc, char** argv)
{      
    // Check Command Line Arguments
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " student_file request_file" << "\n";
        return 1;
    }

    // Open student file
    ifstream studentFile(argv[1]);
    if(!studentFile){
        cerr << "Error: " << argv[1] << " could not be opened" << "\n";
        return 2;
    }

    // Open request file
    ifstream requestsFile(argv[2]);
    if(!requestsFile){
        cerr << "Error: " << argv[2] << " could not be opened" << "\n";
        return 3;
    }

    StudentList students = readStudentList(studentFile);
    printStudentNames(cout, students);

    processEnrollmentRequests(requestsFile, students);
    printStudentSchedules(cout, students);

    return 0;
}

//------------------------------------------------------------------------------
void trim(std::string& str)
{
    if (str.empty()) {
        return;
    }

    int first_nonspace = str.find_first_not_of(" \t");
    int last_non_space = str.find_last_not_of(" \t");

    str = str.substr(first_nonspace, last_non_space + 1);
}

//------------------------------------------------------------------------------
std::istream& operator>>(std::istream& ins, Student& rd)
{
    std::string     nextName;

    getline(ins, nextName);
    trim(nextName);

    rd = Student(nextName);

    return ins;
}

//------------------------------------------------------------------------------
vector<Student> readStudentList(std::istream& ins)
{
    vector<Student> students;

    std::istream_iterator<Student> ins_it(ins);
    std::istream_iterator<Student> ins_end;
    std::copy(ins_it, ins_end, back_inserter(students));

    return students;
}

//------------------------------------------------------------------------------
void printStudentNames(std::ostream& outs, const StudentList& students)
{
    outs << "\n"
         << "Student List"  << "\n"
         << std::string(42, '-') << "\n";

    for (const Student& student : students) {
        outs << " " << student.getName() << "\n";
    }
}

//------------------------------------------------------------------------------
void processEnrollmentRequests(std::istream& ins, StudentList& students)
{
    std::string studentName;    

    cout << "\n"
         << "Enrollment Request Log"  << "\n"
         << std::string(42, '-') << "\n";

    ins >> ws;
    while (getline(ins, studentName, ';')) {
        Course nextCourse;

        ins >> ws >> nextCourse;

        StudentList::iterator it = find(students.begin(), 
                                        students.end(), 
                                        Student(studentName));

        if (it != students.end()) {
            bool success;
            success = it->enrollIn(nextCourse);

            std::string resultStr = (success ? "WAS" : "WAS NOT");

            cout << it->getName() << " "
                 << resultStr     << " enrolled in " 
                 << nextCourse.getNumber()  << "\n";
        }

        ins >> ws;
    }
}

//------------------------------------------------------------------------------
void printStudentSchedules(std::ostream& outs, const StudentList& students)
{
    outs << "\n"
         << "Student Schedule Report"  << "\n"
         << std::string(42, '-') << "\n";

    std::ostream_iterator<Student> outs_it(outs, "\n");
    std::copy(students.begin(), students.end(), outs_it);
}