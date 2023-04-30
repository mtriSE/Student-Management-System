#include "Student.h"

Student::Student(){}
Student::Student(string name, string id,string email)  : name(name), id(id), email(email) {}

string Student::getName() {
    return name;
}

string Student::getId() {
    return id;
}

string Student::getEmail() {
    return email;
}

void Student::enrollCourse(string course_name, string course_ID)  {
    enrolledCourses_name.push_back(course_name);
    enrolledCourses_ID.push_back(course_ID);
}

void Student::printCourse() {
    for (int i = 0; i < enrolledCourses_ID.size(); i++) {
        cout << enrolledCourses_name[i] << " - " << enrolledCourses_ID[i] << "\n";
    }
}

StudentList::StudentList(){}

void StudentList::addStudent(Student* student) {
    students.push_back(student);
}

Student* StudentList::getStudent(string student_info) {
    for (int i = 0; i < students.size(); i++) {
        if (students[i]->getName() == student_info || students[i]->getId() == student_info ) {
            return students[i];
        }
    }
    return NULL;
}

void StudentList::printStudents() {
    if (students.empty()) {
        cout << "None of student.\n";
        return;
    }
    for (int i = 0; i < students.size(); i++) {
        cout << students[i]->getName() << " - " << students[i]->getId() << " - " << students[i]->getEmail() << endl;
    }
}


