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

protected:
    bool getInfo(Course *&course, Student *&student)
    {
        string student_info;
        string course_info;

        cout << "Name\\ID of Student: ";
        getline(cin, student_info);

        cout << "Name\\ID of Course: ";
        getline(cin, course_info);

        student = all_students->getStudent(student_info);
        course = all_courses->getCourse(course_info);

        if (!course && !student) {
            cout << "No info of course and student\n";
            return false;
        }

        if (!course) {
            cout << "No info of course\n";
            return false;
        }

        if (!student) {
            cout << "No info of student\n";
            return false;
        }

        return true;
    }

    bool getInfoForFile(stringstream& ss_std_cour, Course *&course, Student *&student){
        string student_id_info;
        string course_id_info;

        ss_std_cour >> student_id_info >> course_id_info;

        student = all_students->getStudent(student_id_info);
        course = all_courses->getCourse(course_id_info);

        // No info of course and student
        if (!course && !student) return false;

        // No info of course
        if (!course) return false;

        // No info of student
        if (!student) return false;

        return true;
    }

    void assignForFile(stringstream& Ss) {
        Course *course;
        Student *student;

        bool success = getInfoForFile(Ss,course, student);

        if (success)
        {
            
            Grading *grade = new Grading(student);
            student->enrollCourse(course->getCourseName(), course->getCourseID());
            course->enrollStudent(grade);
            
        }
    }

    void recordScoreForFile(stringstream& ss_std_cour, stringstream& ss_score)//chua lam
    {
        Course *course;
        Student *student;
        double score;
        bool success = getInfoForFile(ss_std_cour, course, student);
        if (success)
        {
            // cout << "Score: ";
            while (ss_score >> score){
                course->recordScore(student, score);
            }
        }
    }

    bool getCourseInfo(Course *&course)
    {
        string course_info;

        cout << "Name\\ID of Course: ";
        getline(cin, course_info);

        course = all_courses->getCourse(course_info);

        if (!course)
        {
            cout << "No info of course\n";
            return false;
        }
        return true;
    }

    bool getStudentInfo(Student *&student)
    {
        string student_info;

        cout << "Name\\ID of Student: ";
        getline(cin, student_info);

        student = all_students->getStudent(student_info);
        if (!student)
        {
            cout << "No info of student\n";
            return false;
        }

        return true;
    }

    void updateGradingFile(string student_id_arg, string course_id_arg, double score_to_add)
    {
        fstream *new_file = new fstream("new_grading_file.csv", ios::out | ios::trunc);
        grading_file = new fstream(FILEPATH_GRADING, ios::in);

        string line;
        string std_id;
        string course_id;

        long position_now_from_begin = 0;

        while (!grading_file->eof()) {
            line.clear();
            getline(*grading_file,line);

            if(line == "") {
                
                break;
            }
            position_now_from_begin+=line.length();
            int first_comma = line.find(',');
            std_id = line.substr(0,first_comma);

            size_t second_comma = line.find(',',first_comma+1);
            if (second_comma != string::npos)   course_id = line.substr(first_comma+1, second_comma-first_comma-1);
            else course_id = line.substr(first_comma+1);

            if (std_id == student_id_arg && course_id_arg == course_id) {
        
            ostringstream os;
            if ((int)score_to_add != score_to_add) os << std::fixed << std::setprecision(1);
            os << score_to_add;
            if (second_comma == std::string::npos) // havent had score yet
                line = line + "," + os.str() ;
            else 
                line = line + ";" + os.str() ;
            } 

            line.append("\n");
            new_file->write(line.c_str(),line.length());

        }


        new_file->close();
        grading_file->close();

        remove(FILEPATH_GRADING);
        rename("new_grading_file.csv",FILEPATH_GRADING);

        // for 

        delete new_file;
        delete grading_file;


    }

    void loadData(){
        // load all student from database
        this->student_file = new fstream(FILEPATH_STUDENT,ios::in);
        string line_in_student_file = "";
        while (!student_file->eof()) {
            line_in_student_file.clear();
            getline(*student_file,line_in_student_file);
            if (line_in_student_file.length()==1) return;
            size_t first_comma = line_in_student_file.find(','); 
            size_t second_comma = line_in_student_file.find(',',first_comma+1);

            this->all_students->addStudent(
                new Student(
                    line_in_student_file.substr(first_comma+1,second_comma-first_comma-1),
                    line_in_student_file.substr(0,first_comma),
                    line_in_student_file.substr(second_comma+1)
                )
            );
        }
        student_file->close();
        delete student_file;


        //load all course from database
        this->course_file = new fstream(FILEPATH_COURSE,ios::in);
        string line_in_course_file="";
        while (!course_file->eof()){
            line_in_course_file.clear();
            getline(*course_file,line_in_course_file);
            if (line_in_course_file.length()==1) return;
            size_t first_comma = line_in_course_file.find(','); 
            size_t second_comma = line_in_course_file.find(',',first_comma+1);

            all_courses->addCourse(
                new Course(
                    line_in_course_file.substr(first_comma+1,second_comma-first_comma-1),
                    line_in_course_file.substr(0,first_comma),
                    line_in_course_file.substr(second_comma+1)
                )
            );
        }
        course_file->close();
        delete course_file;

    

        // load all grading from database
        this->grading_file = new fstream(FILEPATH_GRADING,ios::in);
        string line_in_grading_file ="";
        stringstream ss_line_in_grading_file;
        while (!grading_file->eof()){
            line_in_grading_file.clear();
            ss_line_in_grading_file.clear();
            
            getline(*grading_file,line_in_grading_file);
            size_t first_comma = line_in_grading_file.find(','); 
            size_t second_comma = line_in_grading_file.find(',',first_comma+1);
            
            ss_line_in_grading_file << line_in_grading_file.substr(0,first_comma) 
                + " " 
                + (
                    second_comma != string::npos ? line_in_grading_file.substr(first_comma+1,second_comma-first_comma-1) : line_in_grading_file.substr(first_comma+1)
                );
            // ss_line_in_grading_file();
            this->assignForFile(ss_line_in_grading_file);
        }
        grading_file->close();
        delete grading_file;


        //load all score of each enroll in grading file
        this->grading_file = new fstream(FILEPATH_GRADING, ios::in);
        // string line_in_grading_file = "";
        while(!grading_file->eof()){
            line_in_grading_file.clear();
            getline(*grading_file,line_in_grading_file);
            size_t first_comma = line_in_grading_file.find(','); 
            size_t second_comma = line_in_grading_file.find(',',first_comma+1);
            
            if (second_comma == string::npos) continue; //that enrollment still havent had score
            
            stringstream ss_std_cour; 
            ss_std_cour.clear();
            ss_std_cour << line_in_grading_file.substr(0,first_comma) << " " << line_in_grading_file.substr(first_comma+1, second_comma-first_comma-1);

            stringstream ss_score; 
            ss_score.clear();
            
            // to get all score, then turn it into stringstream without semi-colon
            string score_line = "";
            score_line = line_in_grading_file.substr(second_comma+1);
            size_t pos_semi_colon = score_line.find(';');
            while (pos_semi_colon != string::npos){
                score_line.replace(pos_semi_colon,1," ");
                pos_semi_colon = score_line.find(';');
            }

            ss_score << score_line;
            
            this->recordScoreForFile(ss_std_cour,ss_score);
        }
        grading_file->close();
        delete grading_file;
    }   

public:
    void command()
    {
        cout << "0. Quit\n";
        cout << "1. Add a student\n";
        cout << "2. Add a course\n";
        cout << "3. Assign a student to a course\n";
        cout << "4. Record Score\n";
        cout << "5. Get GPA\n";
        cout << "6. Show List of Student of a Course\n";
        cout << "7. Show List of Course of a Student\n";
        cout << "8. Show all Courses\n";
        cout << "9. Show all Students\n";

        // g_int = 0;
    }
    System()
    {
        this->all_students = new StudentList();
        this->all_courses = new CourseList();

        loadData();
    }



    void addStudent()
    {
        string name;
        string ID;
        string email;

        cout << "Name: ";
        getline(cin, name);

        cout << "ID: ";
        getline(cin, ID);

        cout << "Email: ";
        getline(cin, email);

        student_file = new fstream(FILEPATH_STUDENT, ios::out | ios::app);

        string temp =  ID + "," + name + "," + email + "\n";
        student_file->write(temp.c_str(), temp.length());

        all_students->addStudent(new Student(name, ID, email));

        cout << "Completed.\n";
        student_file->close();

        delete student_file;
        student_file = NULL;
    }

    void addCourse()
    {
        string name;
        string ID;
        string instructor;

        cout << "Name: ";
        getline(cin, name);

        cout << "ID: ";
        getline(cin, ID);

        cout << "Instructor: ";
        getline(cin, instructor);

        course_file = new fstream(FILEPATH_COURSE, ios::out | ios::app);

        string temp = ID + "," + name + "," + instructor + "\n";
        course_file->write(temp.c_str(), temp.length());

        this->all_courses->addCourse(new Course(name, ID, instructor));
        cout << "Completed.\n";
        course_file->close();

        delete course_file;
        course_file = NULL;
    }

    void assign()
    {
        Course *course;
        Student *student;
        bool success = getInfo(course, student);

        if (success)
        {

            // make student's grading information
            Grading *grade = new Grading(student);
            student->enrollCourse(course->getCourseName(), course->getCourseID());
            course->enrollStudent(grade);
            cout << "Assign completed.\n";
           
            // write information into file "grading.csv"
            grading_file = new fstream(FILEPATH_GRADING, ios_base::out | ios_base::app);
            string temp = student->getId() + "," + course->getCourseID() + "\n";
            grading_file->write(temp.c_str(), temp.length());
            grading_file->close();
            delete grading_file;
            grading_file = NULL;
        }
    }

    void recordScore()
    {
        Course *course;
        Student *student;
        double score;
        bool success = getInfo(course, student);
        if (success)
        {
            cout << "Score: ";
            cin >> score;
            course->recordScore(student, score);
            updateGradingFile(student->getId(),course->getCourseID(),score);
        }
    }

    void getGPA()
    {
        Course *course;
        Student *student;
        bool success = getInfo(course, student);
        if (success)
        {
            cout << "GPA of " << student->getName() << " in " << course->getCourseName() << ": " << course->getGPA(student) << "\n";
        }
    }

    void getStudentsInCourse()
    {
        Course *course;
        bool success = getCourseInfo(course);
        if (success)
        {
            cout << "List Students of " << course->getCourseName() << ":\n";
            course->printStudent();
        }
    }

    void getCoursesInStudent()
    {
        Student *student;
        bool success = getStudentInfo(student);
        if (success)
        {
            cout << "List Courses of " << student->getName() << ":\n";
            student->printCourse();
        }
    }

    void printStudents()
    {
        cout << "List of All students:\n";
        cout << "Name - ID - Email\n";
        all_students->printStudents();
    }

    void printCourses()
    {
        cout << "List of All Courses:\n";
        cout << "Name - ID - Instructor\n";
        all_courses->printCourses();
    }
};

#endif // SYSTEM_H