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

#endif
