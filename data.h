#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_USERS = 150;
const int MAX_STUDENTS = 120;
const int MAX_ROOMS = 30;

// Role constants
const int SUPER_ADMIN = 0;
const int MANAGER = 1;
const int STUDENT = 2;

// User structure and data
struct User {
    string username;
    string password;
    int role;
};

User users[MAX_USERS];
int userCount = 0;

// Student structure and data
struct Student {
    string username;
    string fullName;
    string rollNo;
    string degree;
    int semester;
    int room;
};

Student students[MAX_STUDENTS];
int studentCount = 0;

// Room structure and data
struct Room {
    int roomNumber;
    int occupancy;
    string student1;
    string student2;
    string student3;
    string student4;
};

Room rooms[MAX_ROOMS];
int roomCount = 0;

// Global login context
string loggedUsername;
int loggedRole = -1;
string loggedRollNo;

#endif
