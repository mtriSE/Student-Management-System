#pragma once
#ifndef GRADING_H
#define GRADING_H

#include "Student.h"

using namespace std;


class Grading { // Academic Transcript of Student
private:
    Student* student;
    vector<double> score;

public:
    Grading(Student* student);

    void addScore(double score);
    Student* getStudent();
    vector<double> getScore();
    double getGPA();
};

#endif // GRADING_H