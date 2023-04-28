#pragma once
#ifndef COURSE_H
#define COURSE_H

#include "Grading.h"
using namespace std;

// fstream student_tbl;
// fstream course_tbl;

// int g_int;

class Course {
private:
    string course_name;
    string course_ID;
    string instructor;
    vector<Grading*> enrolledStudents;

public:
    Course(string course_name, string course_ID, string instructor) : course_name(course_name), course_ID(course_ID), instructor(instructor) {}

    string getCourseName() {
        return course_name;
    }

    string getCourseID() {
        return course_ID;
    }

    string getInstructor() {
        return instructor;
    }

    void enrollStudent(Grading* grade) {
        enrolledStudents.push_back(grade);
    }

    void recordScore(Student* student, double score) {
        for (int i = 0; i < enrolledStudents.size(); i++) {
            if (enrolledStudents[i]->getStudent() == student) {
                enrolledStudents[i]->addScore(score);
                return;
            }
        }
        cout << "No student in this course\n";
    }

    double getGPA (Student* student) {
        for (int i = 0; i < enrolledStudents.size(); i++) {
            if (enrolledStudents[i]->getStudent() == student) {
                return enrolledStudents[i]->getGPA();
            }
        }
        return -1;
    }

    void printStudent() {
        for (int i = 0; i < enrolledStudents.size(); i++) {
            cout << enrolledStudents[i]->getStudent()->getName() << " - " << enrolledStudents[i]->getStudent()->getId() << "\n";
        }
    }


};

class CourseList {
    
private:
    vector<Course*> courses;


public:
    CourseList() {}

    void addCourse(Course* course) {
        courses.push_back(course);
    }

    void printCourses() {
        if (courses.empty()) {
            cout << "None of course\n";
            return;
        }
        for (int i = 0; i < courses.size(); i++) {
            cout << courses[i]->getCourseName() << " - " << courses[i]->getCourseID() << " - " << courses[i]->getInstructor() << endl;
        }
    }
    Course* getCourse(string course_info) {
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i]->getCourseName() == course_info || courses[i]->getCourseID() == course_info) {
                return courses[i];
            }
        }
        return NULL;
    }


};

#endif // COURSE_H