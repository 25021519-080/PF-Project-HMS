#ifndef ROLES_H
#define ROLES_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isUsernameUnique(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return false;
    }
    return true;
}

int findUserByUsername(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return i;
    }
    return -1;
}

string getRoleName(int role) {
    if (role == 0) return "Super Admin";
    if (role == 1) return "Manager";
    if (role == 2) return "Student";
    return "Unknown";
}

bool validatePassword(string password) {
    return password.length() >= 6;
}

void initializeSystem() {
    ifstream file("user.txt");
    if (!file.is_open()) {
        ofstream newfile("user.txt");
        newfile << "1\nadmin\nadmin123\n0\n";
        newfile.close();
    }
    file.close();
}

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

void loadUsers() {
    ifstream file("user.txt");
    if (!file.is_open()) return;
    file >> userCount;
    file.ignore();
    for (int i = 0; i < userCount; i++) {
        file >> users[i].username >> users[i].password >> users[i].role;
    }
    file.close();
}

#endif
