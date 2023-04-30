#include "Grading.h"

Grading::Grading(Student* student) : student(student) {}

void Grading::addScore(double score) {
    this->score.push_back(score);
}

Student* Grading::getStudent() {
    return student;
}

vector<double> Grading::getScore() {
    return score;
}

double Grading::getGPA() {
    double gpa = 0;
    for (int i = 0; i < score.size(); i++) {
        gpa += score[i];
    }
    return 1.0*gpa / score.size(); 
}
