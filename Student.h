#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include "main.h"
using namespace std;


class Student {
private:
    string name;
    string id;
    string email;
    vector<string> enrolledCourses_ID;
    vector<string> enrolledCourses_name;

public:
    Student();
    Student(string name, string id, string email);

    string getName();
    string getId();
    string getEmail();
    void enrollCourse(string course_name, string course_ID);
    void printCourse();
};

class StudentList {

private:
    vector<Student*> students;

public:
    StudentList();

    void addStudent(Student* student);
    Student* getStudent(string student_info);
    void printStudents();
};

#endif // STUDENT_H