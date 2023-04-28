#pragma once
#ifndef GRADING_H
#define GRADING_H

#include "Student.h"

using namespace std;

// fstream student_tbl;
// fstream course_tbl;

// int g_int;


class Grading { // Academic Transcript of Student
private:
    Student* student;
    vector<double> score;

public:
    Grading(Student* student) : student(student) {}

    //need to add score to this student* => must have fstream here
    void addScore(double score) {
        this->score.push_back(score);
    }

    Student* getStudent() {
        return student;
    }

    vector<double> getScore() {
        return score;
    }

    double getGPA() {
        double gpa = 0;
        for (int i = 0; i < score.size(); i++) {
            gpa += score[i];
        }
        return 1.0*gpa / score.size(); 
    }

};

#endif // GRADING_H