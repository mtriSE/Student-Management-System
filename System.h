#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include "Course.h"

#include <fstream>
#include <iomanip>

#define FILEPATH_STUDENT "student.csv"
#define FILEPATH_COURSE "course.csv"
#define FILEPATH_GRADING "grading.csv"

class System
{
private:
    StudentList *all_students;
    CourseList *all_courses;

    fstream *student_file;
    fstream *course_file;
    fstream *grading_file;

private:
    bool getInfo(Course *&course, Student *&student);

    bool getCourseInfo(Course *&course);
    bool getStudentInfo(Student *&student);
    bool getInfoForFile(stringstream &ss_std_cour, Course *&course, Student *&student);
    void assignForFile(stringstream &Ss);
    void recordScoreForFile(stringstream &ss_std_cour, stringstream &ss_score);

    void updateGradingFile(string student_id_arg, string course_id_arg, double score_to_add);
    void loadData();

public:
    System();
    void command();
    void addStudent();
    void addCourse();   
    void assign();
    void recordScore();
    void getGPA();
    void getStudentsInCourse();
    void getCoursesInStudent();
    void printStudents();
    void printCourses();
};

#endif // SYSTEM_H