#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#endif // STUDENT_H

using namespace std;

struct Student {
    int ID;
    string name;
    int age;
    string course;
};

void addStudent(vector<Student>& student);
void displayStudents(const vector<Student>& student);
void searchStudent(const vector<Student>& student);
void updateStudent(vector<Student>& student);
void deleteStudent(vector<Student>& student);

