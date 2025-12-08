#ifndef ROLES_H
#define ROLES_H
#include <iostream>
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

#endif
