#ifndef ROOMS_H
#define ROOMS_H
#include <iostream>
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

#endif
