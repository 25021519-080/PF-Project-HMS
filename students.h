#ifndef STUDENTS_H
#define STUDENTS_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

// Helper function to find student by roll number
int findStudentByRollNo(string rollNo) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo) return i;
    }
    return -1;
}

// Helper function to find by username
int findStudentByUsername(string username) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].username == username) return i;
    }
    return -1;
}

void loadStudents() {
    ifstream file("students.txt");
    if (!file.is_open()) {
        return;
    }
    
    file >> studentCount;
    file.ignore();
    
    for (int i = 0; i < studentCount; i++) {
        getline(file, students[i].username);
        getline(file, students[i].fullName);
        getline(file, students[i].rollNo);
        getline(file, students[i].degree);
        file >> students[i].semester;
        file >> students[i].room;
        file.ignore();
    }
    
    file.close();
}

void saveStudents() {
    ofstream file("students.txt");
    file << studentCount << endl;
    for (int i = 0; i < studentCount; i++) {
        file << students[i].username << endl;
        file << students[i].fullName << endl;
        file << students[i].rollNo << endl;
        file << students[i].degree << endl;
        file << students[i].semester << endl;
        file << students[i].room << endl;
    }
    file.close();
}

#endif
