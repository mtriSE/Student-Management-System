#include "Course.h"

Course::Course(string course_name, string course_ID, string instructor) : course_name(course_name), course_ID(course_ID), instructor(instructor) {}

string Course::getCourseName() {
    return course_name;
}

string Course::getCourseID() {
    return course_ID;
}

string Course::getInstructor() {
    return instructor;
}

void Course::enrollStudent(Grading *grade) {
    enrolledStudents.push_back(grade);
}

void Course::recordScore(Student *student, double score) {
    for (int i = 0; i < enrolledStudents.size(); i++)
    {
        if (enrolledStudents[i]->getStudent() == student)
        {
            enrolledStudents[i]->addScore(score);
            return;
        }
    }
    cout << "No student in this course\n";
}

double Course::getGPA(Student *student) {
    for (int i = 0; i < enrolledStudents.size(); i++)
    {
        if (enrolledStudents[i]->getStudent() == student)
        {
            return enrolledStudents[i]->getGPA();
        }
    }
    return -1;
}

void Course::printStudent() {
    for (int i = 0; i < enrolledStudents.size(); i++)
    {
        cout << enrolledStudents[i]->getStudent()->getName() << " - " << enrolledStudents[i]->getStudent()->getId() << "\n";
    }
}

CourseList::CourseList() {}

void CourseList::addCourse(Course* course) {
    courses.push_back(course);
}

void CourseList::printCourses() {
    if (courses.empty()) {
        cout << "None of course\n";
        return;
    }
    for (int i = 0; i < courses.size(); i++) {
        cout << courses[i]->getCourseName() << " - " << courses[i]->getCourseID() << " - " << courses[i]->getInstructor() << endl;
    }
}
Course* CourseList::getCourse(string course_info) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i]->getCourseName() == course_info || courses[i]->getCourseID() == course_info) {
            return courses[i];
        }
    }
    return NULL;
}