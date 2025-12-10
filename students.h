#ifndef STUDENTS_H
#define STUDENTS_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

void saveUsers();
bool isUsernameUnique(string username);

int findStudentByRollNo(string rollNo) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo) return i;
    }
    return -1;
}

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

void admitStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Max students reached!" << endl;
        return;
    }
    
    cout << "Full Name: ";
    string fullName;
    getline(cin, fullName);
    

    cout << "Username (for login): ";
    string username;
    getline(cin, username);
    
    if (!isUsernameUnique(username)) {
        cout << "Username already exists! Please create a unique one." << endl;
        return;
    }
    
    cout << "Degree: ";
    string degree;
    getline(cin, degree);
    
    cout << "Semester (1-8): ";
    int semester;
    cin >> semester;
    cin.ignore(1000, '\n');
    
    if (semester < 1 || semester > 8) {
        cout << "Invalid semester! Must be between 1-8." << endl;
        return;
    }
    
    cout << "Roll Number: ";
    string rollNo;
    getline(cin, rollNo);
    
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo) {
            cout << "Student with this roll number already exists!" << endl;
            return;
        }
    }
    
    students[studentCount].username = username;
    students[studentCount].fullName = fullName;
    students[studentCount].rollNo = rollNo;
    students[studentCount].degree = degree;
    students[studentCount].semester = semester;
    students[studentCount].room = 0;
    
    studentCount++;
    saveStudents();
    
    if (userCount < MAX_USERS) {
        users[userCount].username = username;
        // password will be set on the login
        users[userCount].password = "";
        users[userCount].role = STUDENT;
        userCount++;
        saveUsers();
        cout << "Student admitted! Username: " << username << " | Full Name: " << fullName << " | Role: Student" << endl;
        cout << "Student will set password on first login." << endl;
    } else {
        cout << "Student admitted! But user account could not be created (user limit reached)." << endl;
    }
}

#endif
