#ifndef ROLES_H
#define ROLES_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

// check if username is unique 
bool isUsernameUnique(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return false;
    }
    for (int i = 0; i < studentCount; i++) {
        if (students[i].username == username) return false;
    }
    return true;
}

// username say user ko find karna
int findUserByUsername(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return i;
    }
    return -1;
}

// role id say role name return kiya
string getRoleName(int role) {
    if (role == 0) return "Super Admin";
    if (role == 1) return "Manager";
    if (role == 2) return "Student";
    return "Unknown";
}

// ye function jab bhi main file run hogi chalai ga
void initializeSystem() {
    ifstream file("user.txt");
    if (!file.is_open()) {
        cout << "Creating default admin user..." << endl;
        ofstream newfile("user.txt");
        newfile << "1" << endl;
        newfile << "admin" << endl;
        newfile << "admin123" << endl;
        newfile << "0" << endl;
        newfile.close();
        file.open("user.txt");
    }
    file >> userCount;
    file.ignore();
    for (int i = 0; i < userCount; i++) {
        getline(file, users[i].username);
        getline(file, users[i].password);
        file >> users[i].role;
        file.ignore();
    }
    file.close();
}

// new users ko file mai store karna
void saveUsers() {
    ofstream file("user.txt");
    file << userCount << endl;
    for (int i = 0; i < userCount; i++) {
        file << users[i].username << endl;
        file << users[i].password << endl;
        file << users[i].role << endl;
    }
    file.close();
}

// basic login with password check
bool loginUser() {
    cout << "Username: ";
    string username;
    cin >> username;
    cin.ignore();
    
    int idx = findUserByUsername(username);
    if (idx == -1) {
        cout << "User not found!" << endl;
        return false;
    }
    
    cout << "Password: ";
    string password;
    getline(cin, password);
    
    if (users[idx].password != password) {
        cout << "Wrong password!" << endl;
        return false;
    }
    
    loggedUsername = users[idx].username;
    loggedRole = users[idx].role;
    loggedRollNo = "";
    cout << "Login successful!" << endl;
    return true;
}

// ye new users create karne ke liye
void createUser() {
    if (userCount >= MAX_USERS) {
        cout << "Maximum users reached!" << endl;
        return;
    }
    cout << "New username: ";
    string username;
    cin >> username;
    cin.ignore();
    
    if (!isUsernameUnique(username)) {
        cout << "Username already exists!" << endl;
        return;
    }
    
    cout << "Password: ";
    string password;
    getline(cin, password);
    
    cout << "Role (0=Super Admin, 1=Manager): ";
    int role;
    cin >> role;
    cin.ignore();
    
    if (role < 0 || role > 1) {
        cout << "Invalid role!" << endl;
        return;
    }
    
    users[userCount].username = username;
    users[userCount].password = password;
    users[userCount].role = role;
    userCount++;
    saveUsers();
    cout << "User created!" << endl;
}

#endif
