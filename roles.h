#ifndef ROLES_H
#define ROLES_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

// check if username is unique 
// kunke ham roles ko differentiate username ki base par
// karte hain

bool isUsernameUnique(string username) {
    // both students aur roeles mai check karen gay.
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return false;
    }
    for (int i = 0; i < studentCount; i++) {
        if (students[i].username == username) return false;
    }
    return true;
}

// username say user ko find karna.
// basically ham username say array index find karain gay
// we can then use index to find anything else about the user.

int findUserByUsername(string username) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) return i;
    }

    // agar nai mila to retun -1. 
    // -1 ka logic already explained hai main cpp file mai.
    return -1;
}

// role id say role name return kiya.
string getRoleName(int role) {
    if (role == 0) return "Super Admin";
    if (role == 1) return "Manager";
    if (role == 2) return "Student";
    return "Unknown";
}


// ye function jab bhi main file run hogi chalai ga.

void initializeSystem() {
    // file "user.txt" ko "read" kro
    ifstream file("user.txt");
    // agar file exist nahi karti tou new banao
    if (!file.is_open()) {
        // new file mai aik superadmin create karo 
        // so that wo new users create karsakay
        cout << "Creating default admin user..." << endl;
        ofstream newfile("user.txt");
        newfile << "1" << endl;
        newfile << "admin" << endl;
        newfile << "admin123" << endl;
        newfile << "0" << endl;
        newfile.close();
        // file ko memory mai load kiya
        // takay bar bar use easily kar lain
        file.open("user.txt");
    }
    // usercount file say nikal kar userCount mai store kiya
    // acha "file >> userCount" sirf first line ko store karay ga
    // and we know that first line is the user count.
    file >> userCount;
    // aur new like ko ignore kardo, same as cin.ignore()
    file.ignore();
    
    // jitne bhi users aur passwrods hain unko load karlo 
    // memeory mai, so that bar bar easily access kar sakain
    for (int i = 0; i < userCount; i++) {
        getline(file, users[i].username);
        getline(file, users[i].password);
        file >> users[i].role;
        file.ignore();
    }
    // yahan ham file close isliye kar rhe takay doosray fucntions
    // is file ko use kar sakain. 
    // agar nahi tou file yahan lock hojayaye gi
    file.close();
}


// new userss ko from the memory file mai store kartay
// acha jo puranay hain, wo rewrite hotay hain
// lekin koi issue nahi kyunke wo same hi hain.

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


// ye login function main file mai call hota hai
// to login
// ye bool isliye hai kyuke hamnay true yan false return karna
// hai so that we know if login was successful or not.
bool loginUser() {
    // asking user to enter username
    cout << "Username: ";
    string username;
    cin >> username;
    cin.ignore();
    
    // idx is basically the array index of the username
    // ham yahan "findUserByUsername" ko call karain gay
    // so that we get the array index, e.g [1], [2], etc.
    int idx = findUserByUsername(username);
    // ye -1 upar wala function return kraay ga
    // agar -1 matalab wo username exist nahi karta
    if (idx == -1) {
        cout << "User not found!" << endl;
        // yani login unsucessful, so retun false.
        // yahan par login function end hojaye ga
        // kyunke early retun kardiya.
        return false;
    }
    
    // agar username milgya, yaani idx bhi milgayi
    // ab ham check karain gay ke is idx walay user ka password
    // hai yan nahi, agar nahi tou user ko bolo set karo. 
    if (users[idx].password == "") {
        cout << "First login - Set your password" << endl;
        cout << "Password: ";
        string password1;
        // acha yahan ham cin >> password1 isliye use nahi kar rhe
        // kyunke cin spaces ignore kardeta, password can contain spaces
        // isliye getline ppori line ko password1 mai store karday ga.
        getline(cin, password1);

        // aik dafa confirm karo password
        cout << "Confirm Password: ";
        string password2;
        getline(cin, password2);
        
        // agar match karta tou theek warna return false
        if (password1 != password2) {
            cout << "Passwords do not match!" << endl;
            return false;
        }
        // ab jab user password set karleta tou usay uski 
        // idx mai daal do 
        users[idx].password = password1;
        // new user ko save karne ke liye "saveUsers" function 
        // call kiya
        saveUsers();
        cout << "Password set successfully!" << endl;

    // agar password already exist karta tha tou poocho user say
    } else {
        cout << "Password: ";
        string password;
        getline(cin, password);
        // agai match karta tou theek warna return false.
        if (users[idx].password != password) {
            cout << "Wrong password!" << endl;
            return false;
        }
    }
    // jab username aur password wala kaam hojaye
    // tou looged username mai isi idx ka username aur uska roll daal do.
    loggedUsername = users[idx].username;
    loggedRole = users[idx].role;
    // yahan par roll number empty hai 
    // ye roll no sirf student ko milay ga, main cpp file wali file say
    // main cpp ka code:
    /* if (loginUser()) {                    // Login successful
    // If student logged in, to roll no set kardo
    if (loggedRole == 2) {            // Only for students (role 2)
        loggedRollNo = getRollNumberByName(loggedUsername); 
    }
    */
    
    loggedRollNo = "";
    // hogya login, welcome, return true.
    cout << "Login successful! Welcome " << loggedUsername << endl;
    return true;
}

// ye new users create karne ke liye
// ye option sirf super admin ke pass hi hai

void createUser() {
    // agar max hain tou dont create more
    if (userCount >= MAX_USERS) {
        cout << "Maximum users reached!" << endl;
        return;
    }
    // nahi max, tou poocha username 
    cout << "New username: ";
    string username;
    cin >> username;
    cin.ignore();
    
// dekho username pehle exist karta ke nahi
// "isUsernameUnique" yan tou true, yan false return karta, 
// agar false, tou bata do username exists.
    if (!isUsernameUnique(username)) {
        cout << "Username already exists. Please create a unique one." << endl;
        return;
    }
// agar nahi unique, then ask for the role. 
    cout << "Role (0=Super Admin, 1=Manager): ";
    int role;
    cin >> role;
    cin.ignore();

// role should only be 0, 1
// students wala 2 option sirf admit student walay option say show hoga    
    if (role < 0 || role > 1) {
        cout << "Invalid role! Must be 0 or 1 (create students from admit student option)" << endl;
        return;
    }
// ab usercount, yani latest array ki index mai is new user ko 
// store kardo, basicllay array tou [0] say start hoti
// jabkay user count 1 say, isliye total count matlab
// latest array index entry      
    users[userCount].username = username;
    users[userCount].password = "";  // Empty password for first login setup
    users[userCount].role = role;

  // ab isme aik ka increment kardo  
    userCount++;
  // phir say new users save kardo
    saveUsers();
  // user ko bata do ke user bangya  
    cout << "User created!" << endl;
    cout << "User will set password on first login." << endl;
}

// usernames ko role assign karne ke liye

void assignRole() {
    // ask for username
    cout << "Username: ";
    string username;
    cin >> username;
    cin.ignore();
    // again dekho username exist karta..
    int idx = findUserByUsername(username);
    // if not just tell the user
    if (idx == -1) {
        cout << "User not found!" << endl;
        return;
    }
    // poocho konsa role dena
    cout << "New role (0=Super Admin, 1=Manager): ";
    int role;
    cin >> role;
    cin.ignore();
    // dekho 0, 1 hai yan nahi
    if (role < 0 || role > 1) {
        cout << "Invalid role! Must be 0 or 1 (Student role can only be assigned via Admit Student)." << endl;
        return;
    }
    // ham phir us user ki index ka role change kardain gay
    users[idx].role = role;
    // new role ke sath user ko save kardo
    saveUsers();
    cout << "Role assigned!" << endl;
}

// viewProfile() sirf apka name aur role dikha deti
void viewProfile() {
    cout << "\n=== Your Profile ===" << endl;
    cout << "Username: " << loggedUsername << endl;
    cout << "Role: " << getRoleName(loggedRole) << endl;
}

#endif
