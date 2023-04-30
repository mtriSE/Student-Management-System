#pragma once
#ifndef COURSE_H
#define COURSE_H

#include "Grading.h"
using namespace std;


class Course {
private:
    string course_name;
    string course_ID;
    string instructor;
    vector<Grading*> enrolledStudents;

public:
    Course(string course_name, string course_ID, string instructor);

    string getCourseName();
    string getCourseID();
    string getInstructor();
    void enrollStudent(Grading* grade);
    void recordScore(Student* student, double score);
    double getGPA (Student* student);
    void printStudent();
};

class CourseList {
    
private:
    vector<Course*> courses;

public:
    CourseList();
    void addCourse(Course* course);
    void printCourses();
    Course* getCourse(string course_info);
    
};

#endif // COURSE_H