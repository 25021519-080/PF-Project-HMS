#ifndef ROOMS_H
#define ROOMS_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

// room index id, room number say find karni
// agar hamray pass room 1, 2, 3 hai aur
// admin room 2 delete kardeta, tou ham array ko 
// left par shift kardain gay, so that now room 3 has index 1
// instead of 2
// isliye we need to find the room array index by number

int findRoomByNumber(int roomNum) {
    for (int i = 0; i < roomCount; i++) {
        // loop mai iterate karo aur dekho ke kisi room 
        // ka number provided say milta yan nahi
        if (rooms[i].roomNumber == roomNum) {
            return i;
        }
    }
    // if not return -1 (yani not found)
    return -1;
}


// load rooms is same like load students or roles

void loadRooms() {
    ifstream file("rooms.txt");
    if (!file.is_open()) {
        roomCount = 0;
        return;
    }
    
    file >> roomCount;
    file.ignore();
    // put all the rooms in memory for easy access
    for (int i = 0; i < roomCount; i++) {
        file >> rooms[i].roomNumber;
        file >> rooms[i].occupancy;
        file.ignore();
        getline(file, rooms[i].student1);
        getline(file, rooms[i].student2);
        getline(file, rooms[i].student3);
        getline(file, rooms[i].student4);
    }
    // file close takay kahin aur use kar sakain
    file.close();
}

// save room matlab, varibales say file mai store karnay
// room count ka loop chla kar, array id ki base par room store karna
void saveRooms() {
    ofstream file("rooms.txt");
    file << roomCount << endl;
    
    for (int i = 0; i < roomCount; i++) {
        file << rooms[i].roomNumber << endl;
        file << rooms[i].occupancy << endl;
        file << rooms[i].student1 << endl;
        file << rooms[i].student2 << endl;
        file << rooms[i].student3 << endl;
        file << rooms[i].student4 << endl;
    }
    
    file.close();
}

// create new rooms
void createRoom() {
    if (roomCount >= MAX_ROOMS) {
        cout << "Max rooms reached!" << endl;
        return;
    }
    
    // finding the maximum room number
    int maxRoomNumber = 0;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber > maxRoomNumber) {
            maxRoomNumber = rooms[i].roomNumber;
        }
    }
    
    // new room ab max number ke next wala hoka.
    int newRoomNumber = maxRoomNumber + 1;
    // number assign karidya, baqi cheezan zero
    rooms[roomCount].roomNumber = newRoomNumber;
    rooms[roomCount].occupancy = 0;
    rooms[roomCount].student1 = "";
    rooms[roomCount].student2 = "";
    rooms[roomCount].student3 = "";
    rooms[roomCount].student4 = "";
    // increase it by one  
    roomCount++;
    // save new rooms in memory just like of students
    saveRooms();
    // tell the user, room is created
    cout << "Room " << newRoomNumber << " created!" << endl;
}


// yahan par, student ko room assign karain gay
void assignRoom() {
    cout << "Roll Number: ";
    string rollNo;
    getline(cin, rollNo);
    
    // fir check ke student exist karta ke nahi
    int studentIndex = findStudentByRollNo(rollNo);
    // ab tak pata tou chal gya hoga -1
    if (studentIndex == -1) {
        cout << "Student not found!" << endl;
        return;
    }
    
    // Check agar room already assign hai tou nahi is student ko
    if (students[studentIndex].room != 0) {
        cout << "Student already assigned to room " << students[studentIndex].room << "!" << endl;
        return;
    }
    
    // Show available rooms
    cout << "\n=== Available Rooms ===" << endl;
    //  dekho ke room avaible hain yan nahi
    bool hasAvailableRoom = false;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].occupancy < 4) {
            // jo avauble hain unka data show kardo
            cout << "Room " << rooms[i].roomNumber << " | Occupancy: " << rooms[i].occupancy << "/4" << endl;
            hasAvailableRoom = true;
        }
    }
    // if no rooms just tell the user
    if (!hasAvailableRoom) {
        cout << "No available rooms!" << endl;
        return;
    }
    
    // Get room choice
    cout << "\nEnter Room number: ";
    int roomNum;
    cin >> roomNum;
    cin.ignore();
    
    // see if the room exists 
    int roomIndex = findRoomByNumber(roomNum);
    if (roomIndex == -1) {
        cout << "Room not found!" << endl;
        return;
    }
    // agar jo room user nay choose kiya full hai to bata do 
    if (rooms[roomIndex].occupancy >= 4) {
        cout << "Room is full!" << endl;
        return;
    }
    
    // agar nahi full tou wo room, is student ko assign kardo
    students[studentIndex].room = roomNum;
    
    // usko proper slot mai add karo
    // basiclaly ke agar 1st mai ki banda hai to next one
    // and so on
    if (rooms[roomIndex].occupancy == 0) {
        rooms[roomIndex].student1 = rollNo;
    } else if (rooms[roomIndex].occupancy == 1) {
        rooms[roomIndex].student2 = rollNo;
    } else if (rooms[roomIndex].occupancy == 2) {
        rooms[roomIndex].student3 = rollNo;
    } else if (rooms[roomIndex].occupancy == 3) {
        rooms[roomIndex].student4 = rollNo;
    }
    // occupancy increased by one
    rooms[roomIndex].occupancy++;

    // now student data mai aik student ko new room assign hua to
    // tou students bhi save karo aur room bhi
    saveStudents();
    saveRooms();

    // tell the user, ke kaam hogya
    cout << "Student assigned to room " << roomNum << "!" << endl;
}

// view rooms mai sab rooms ka data
// ye lagta complex hai but easy hai
void viewRooms() {
    // again count = 0, tou no roomss
    if (roomCount == 0) {
        cout << "No rooms!" << endl;
        return;
    }
    // har room count par room number
    // occupancy show karwani
    cout << "\n=== Rooms ===" << endl;
    for (int i = 0; i < roomCount; i++) {
        cout << "Room " << rooms[i].roomNumber;
        cout << " | Occupancy: " << rooms[i].occupancy << "/4";
        // agar occupancy 0 nahi tou show each student if it exists
        if (rooms[i].occupancy > 0) {
            cout << " | Students: " << rooms[i].student1;
            if (rooms[i].occupancy >= 2) cout << ", " << rooms[i].student2;
            if (rooms[i].occupancy >= 3) cout << ", " << rooms[i].student3;
            if (rooms[i].occupancy >= 4) cout << ", " << rooms[i].student4;
        }
        cout << endl;
    }
}


// aik student se room cheen lo
void unassignRoom() {
    cout << "Roll Number to unassign: ";
    string rollNo;
    getline(cin, rollNo);
    
    // Find student
    int studentIndex = findStudentByRollNo(rollNo);
    if (studentIndex == -1) {
        cout << "Student not found!" << endl;
        return;
    }
    
    // Check if assigned to any room
    if (students[studentIndex].room == 0) {
        cout << "Student is not assigned to any room!" << endl;
        return;
    }
    
    // room number find karo aur room number se index
    int roomNumber = students[studentIndex].room;
    int roomIndex = findRoomByNumber(roomNumber);
    
    // agar tou index -1 hai, yaani room exist karta tou remove
    // the user from the slot
    if (roomIndex != -1) {
        // Remove student from room slot
        // dekho kis slot mai hai wo bachha
        if (rooms[roomIndex].student1 == rollNo) {
            rooms[roomIndex].student1 = "";
        } else if (rooms[roomIndex].student2 == rollNo) {
            rooms[roomIndex].student2 = "";
        } else if (rooms[roomIndex].student3 == rollNo) {
            rooms[roomIndex].student3 = "";
        } else if (rooms[roomIndex].student4 == rollNo) {
            rooms[roomIndex].student4 = "";
        }
        // remove karke us room ki occupancy aik kam kardi
        rooms[roomIndex].occupancy--;
        // save new data
        saveRooms();
    }
    
    // pehle hamnay student ko room say remove kiya, ab student
    // say room remove kiya
    students[studentIndex].room = 0;
    saveStudents();
    cout << "Student unassigned from room " << roomNumber << "!" << endl;
}

// show my room
// just check if the logged roll no, is in any room or no
void viewMyRoom() {
    // Find my room number
    int myRoomNumber = 0;
    for (int i = 0; i < studentCount; i++) {
        // agar hamare rool number students mai hai 
        // tou hamata room "myRoomNumber" mai store karlo
        // ham ab "myRoomNumber" say room ki details 
        // lain gay
        if (students[i].rollNo == loggedRollNo) {
            myRoomNumber = students[i].room;
            break;
        }
    }
    
    cout << "\n=== Your Room Assignment ===" << endl;
    // agar koi nahi tou just tell no rooms
    if (myRoomNumber == 0) {
        cout << "You are not assigned to any room yet!" << endl;
        return;
    }
    
    // Find room details from the room number alloted to me
    int roomIndex = findRoomByNumber(myRoomNumber);
    // agar nahi exist karta, return
    if (roomIndex == -1) {
        return;
    }
    
    // show details
    cout << "Room Number: " << myRoomNumber << endl;
    cout << "Occupancy: " << rooms[roomIndex].occupancy << "/4" << endl;
    
    // Show roommates

    bool hasRoommates = false;
    
    // array of all student slots
    // pooray room ke sab students store karliye
    string studentSlots[4] = {
        rooms[roomIndex].student1,
        rooms[roomIndex].student2,
        rooms[roomIndex].student3,
        rooms[roomIndex].student4
    };
    
    // loop through all 4 students aur roommates show karo
    for (int i = 0; i < 4; i++) {
        // check karo ke stundents ki slot empty yan logged user
        // ke sath math tou nahi kar rahi 
        if (studentSlots[i] != "" && studentSlots[i] != loggedRollNo) {
            // jo us slot mai roll number hai uski id find karli
            int idx = findStudentByRollNo(studentSlots[i]);
            if (idx != -1) {
                // agar id -1 nahi yani student hai tou phir
                // wo roomate show karwa do
                if (!hasRoommates) {
                    cout << "\nRoommates:" << endl;
                    hasRoommates = true;
                }
                // us id walay student ki saari details 
                // show karwa do
                cout << "  - " << students[idx].fullName << " (Roll: " << students[idx].rollNo << ")" << endl;
            }
        }
    }
    // agar kkoi roomate nahi aur occupancy 1 hai tou 
    // iska matlab you are alone in that room
    if (!hasRoommates && rooms[roomIndex].occupancy == 1) {
        cout << "You are alone in this room." << endl;
    }
}

#endif
