#ifndef ROOMS_H
#define ROOMS_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int findRoomByNumber(int roomNo) {
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomNo == roomNo) return i;
    }
    return -1;
}

int findRoomByStudent(string username) {
    for (int i = 0; i < roomCount; i++) {
        for (int j = 0; j < 4; j++) {
            if (rooms[i].students[j] == username) return i;
        }
    }
    return -1;
}

bool isRoomFull(int roomNo) {
    int idx = findRoomByNumber(roomNo);
    if (idx == -1) return true;
    return rooms[idx].occupancy >= 4;
}

void loadRooms() {
    ifstream file("rooms.txt");
    if (!file.is_open()) return;
    
    file >> roomCount;
    for (int i = 0; i < roomCount; i++) {
        file >> rooms[i].roomNo >> rooms[i].occupancy;
        file.ignore();
        for (int j = 0; j < 4; j++) {
            getline(file, rooms[i].students[j]);
        }
    }
    file.close();
}

void saveRooms() {
    ofstream file("rooms.txt");
    file << roomCount << endl;
    for (int i = 0; i < roomCount; i++) {
        file << rooms[i].roomNo << " " << rooms[i].occupancy << endl;
        for (int j = 0; j < 4; j++) {
            file << rooms[i].students[j] << endl;
        }
    }
    file.close();
}

#endif
