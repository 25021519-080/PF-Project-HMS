#ifndef STUDENTS_H
#define STUDENTS_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

// doorsi header files say functions yahan declaree kiyye
// so that compiler know these exists
// i have already explained these fucntons in the main files 
void saveUsers();
void saveRooms();
bool isUsernameUnique(string username);

// Helper function to find student by roll number
// sirf user index id return kartay yahan

int findStudentByRollNo(string rollNo) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo) return i;
    }
    return -1;
}

// similar to above function just use username intead of the roll no
int findStudentByUsername(string username) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].username == username) return i;
    }
    return -1;
}
// just like the load users, load rooms
void loadStudents() {
    ifstream file("students.txt");
    if (!file.is_open()) {
        return;
    }
    
    file >> studentCount;
    file.ignore();
    
    // add them in memory
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

// save students from the memory to the file 
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

// admit students 
void admitStudent() {
    // if max reached, dont create more
    if (studentCount >= MAX_STUDENTS) {
        cout << "Max students reached!" << endl;
        return;
    }
    
    // ask for full name 
    cout << "Full Name: ";
    string fullName;
    getline(cin, fullName);
    

    // ask for username
    cout << "Username (for login): ";
    string username;
    getline(cin, username);
    
    // Check if username is unique 
    if (!isUsernameUnique(username)) {
        cout << "Username already exists! Please create a unique one." << endl;
        return;
    }
    
    // ask degree
    cout << "Degree: ";
    string degree;
    getline(cin, degree);
    
    // ask semester
    cout << "Semester (1-8): ";
    int semester;
    cin >> semester;
    cin.ignore(1000, '\n');
    
    // check if sem is between 1-8
    if (semester < 1 || semester > 8) {
        cout << "Invalid semester! Must be between 1-8." << endl;
        return;
    }
    
    // ask for roll no
    cout << "Roll Number: ";
    string rollNo;
    getline(cin, rollNo);
    
    // see if this roll no exists or no
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNo == rollNo) {
            cout << "Student with this roll number already exists!" << endl;
            return;
        }
    }
    
    // if all the above is done, add the student with 
    // studentCount as the index, kyunke its always one above the 
    // stundets array index
    students[studentCount].username = username;
    students[studentCount].fullName = fullName;
    students[studentCount].rollNo = rollNo;
    students[studentCount].degree = degree;
    students[studentCount].semester = semester;
    students[studentCount].room = 0;
    
    // increase the student count by one
    studentCount++;
    // save the students
    saveStudents();
    
    // new students ke liye automatically aik  user create karlo
    if (userCount < MAX_USERS) {
        users[userCount].username = username;
        // password will be set on the login
        users[userCount].password = "";
        users[userCount].role = STUDENT;
        // increase it by one
        userCount++;
        // save the new user data
        saveUsers();
        cout << "Student admitted! Username: " << username << " | Full Name: " << fullName << " | Role: Student" << endl;
        cout << "Student will set password on first login." << endl;
    } else {
        cout << "Student admitted! But user account could not be created (user limit reached)." << endl;
    }
}

// show data of students from the array index
void viewStudents() {
    if (studentCount == 0) {
        cout << "No students!" << endl;
        return;
    }

// iterate through the studentcount, and show data    
    cout << "\n=== Students ===" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << "Username: " << students[i].username << " | Name: " << students[i].fullName 
             << " | Roll No: " << students[i].rollNo << " | " << students[i].degree << " | Sem: " << students[i].semester
             << " | Room: " << students[i].room << endl;
    }
}

// remove student
void removeStudent() {
    cout << "Roll Number to remove: ";
    string rollNo;
    getline(cin, rollNo);
    

    // get student index from the function 
    int studentIndex = findStudentByRollNo(rollNo);
    if (studentIndex == -1) {
        cout << "Student not found!" << endl;
        return;
    }
    
    cout << "Are you sure you want to remove " << students[studentIndex].fullName << "? (yes/no): ";
    string confirm;
    getline(cin, confirm);
    
    if (confirm != "yes") {
        cout << "Cancelled!" << endl;
        return;
    }
    
    string usernameToRemove = students[studentIndex].username;
    
    // Remove user account 
    int userIdx = -1;
    for (int i = 0; i < userCount; i++) {
        // first get user idx
        if (users[i].username == usernameToRemove) {
            userIdx = i;
            break;
        }
    }
    // if user idx not -1, shift the array left on one side
    // kyunke ab jo empty array hogya baqi students wahan par
    // jagah le lain gay
    /* if we have:
    user[0] = aman
    user[1] = sania
    user[2] = afaan,
    if we remove sania, then afaan should have index
    [1] instead of [2]
    */
    if (userIdx != -1) {
        for (int j = userIdx; j < userCount - 1; j++) {
            users[j] = users[j + 1];
        }
        // decrement of 1
        userCount--;
        // save new user data
        saveUsers();
    }
    
    // Remove room assignment 
    for (int i = 0; i < roomCount; i++) {
        // get data of al students
        string studentSlots[4] = {
            rooms[i].student1,
            rooms[i].student2,
            rooms[i].student3,
            rooms[i].student4
        };
        
        for (int j = 0; j < 4; j++) {
            // remove from that specific slot
            if (studentSlots[j] == rollNo) {
                if (j == 0) rooms[i].student1 = "";
                else if (j == 1) rooms[i].student2 = "";
                else if (j == 2) rooms[i].student3 = "";
                else if (j == 3) rooms[i].student4 = "";
                rooms[i].occupancy--;
                break;
            }
        }
    }
    // now save the rooms
    if (roomCount > 0) saveRooms();
    
    // jis trah users ko shift kiya usi trah students ko bhi
    for (int j = studentIndex; j < studentCount - 1; j++) {
        students[j] = students[j + 1];
    }
    // decrement of one
    studentCount--;
    saveStudents();
    cout << "Student removed! (User account and room assignment cleaned up)" << endl;
}
// get roll number of a student from a username
string getRollNumberByName(string username) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].username == username) {
            return students[i].rollNo;
        }
    }
    return "";
}

#endif
