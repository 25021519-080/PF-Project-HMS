#ifndef ROOMS_H
#define ROOMS_H

#include <iostream>
#include <fstream>
#include <string>
#include "data.h"
using namespace std;

// Find room by number
int findRoomByNumber(int roomNum) {
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == roomNum) {
            return i;
        }
    }
    return -1;
}

// Load rooms from file
void loadRooms() {
    ifstream file("rooms.txt");
    if (!file.is_open()) {
        roomCount = 0;
        return;
    }
    
    file >> roomCount;
    file.ignore();
    
    for (int i = 0; i < roomCount; i++) {
        file >> rooms[i].roomNumber;
        file >> rooms[i].occupancy;
        file.ignore();
        getline(file, rooms[i].student1);
        getline(file, rooms[i].student2);
        getline(file, rooms[i].student3);
        getline(file, rooms[i].student4);
    }
    
    file.close();
}

// Save rooms to file
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

// Create new room
void createRoom() {
    if (roomCount >= MAX_ROOMS) {
        cout << "Max rooms reached!" << endl;
        return;
    }
    
    int maxRoomNumber = 0;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber > maxRoomNumber) {
            maxRoomNumber = rooms[i].roomNumber;
        }
    }
    
    int newRoomNumber = maxRoomNumber + 1;
    rooms[roomCount].roomNumber = newRoomNumber;
    rooms[roomCount].occupancy = 0;
    rooms[roomCount].student1 = "";
    rooms[roomCount].student2 = "";
    rooms[roomCount].student3 = "";
    rooms[roomCount].student4 = "";
    
    roomCount++;
    saveRooms();
    cout << "Room " << newRoomNumber << " created!" << endl;
}

// View all rooms
void viewRooms() {
    if (roomCount == 0) {
        cout << "No rooms!" << endl;
        return;
    }
    
    cout << "\n=== Rooms ===" << endl;
    for (int i = 0; i < roomCount; i++) {
        cout << "Room " << rooms[i].roomNumber;
        cout << " | Occupancy: " << rooms[i].occupancy << "/4";
        if (rooms[i].occupancy > 0) {
            cout << " | Students: " << rooms[i].student1;
            if (rooms[i].occupancy >= 2) cout << ", " << rooms[i].student2;
            if (rooms[i].occupancy >= 3) cout << ", " << rooms[i].student3;
            if (rooms[i].occupancy >= 4) cout << ", " << rooms[i].student4;
        }
        cout << endl;
    }
}

#endif
