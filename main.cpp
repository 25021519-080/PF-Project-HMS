#include "data.h"
#include "roles.h"
#include "students.h"
#include "rooms.h"

void superAdminMenu() {
    int choice;
    while (true) {
        cout << "\n=== Super Admin Menu ===" << endl;
        cout << "1. View Profile" << endl;
        cout << "2. Create User" << endl;
        cout << "3. Assign Role" << endl;
        cout << "4. Admit Student" << endl;
        cout << "5. View Students" << endl;
        cout << "6. Remove Student" << endl;
        cout << "7. Create Room" << endl;
        cout << "8. View Rooms" << endl;
        cout << "9. Assign Room" << endl;
        cout << "10. Unassign Room" << endl;
        cout << "11. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        
        if (choice == 1) viewProfile();
        else if (choice == 2) createUser();
        else if (choice == 3) assignRole();
        else if (choice == 4) admitStudent();
        else if (choice == 5) viewStudents();
        else if (choice == 6) removeStudent();
        else if (choice == 7) createRoom();
        else if (choice == 8) viewRooms();
        else if (choice == 9) assignRoom();
        else if (choice == 10) unassignRoom();
        else if (choice == 11) break;
        else cout << "Invalid choice!" << endl;
    }
}

void managerMenu() {
    int choice;
    while (true) {
        cout << "\n=== Manager Menu ===" << endl;
        cout << "1. View Profile" << endl;
        cout << "2. Admit Student" << endl;
        cout << "3. View Students" << endl;
        cout << "4. Remove Student" << endl;
        cout << "5. Create Room" << endl;
        cout << "6. View Rooms" << endl;
        cout << "7. Assign Room" << endl;
        cout << "8. Unassign Room" << endl;
        cout << "9. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        
        if (choice == 1) viewProfile();
        else if (choice == 2) admitStudent();
        else if (choice == 3) viewStudents();
        else if (choice == 4) removeStudent();
        else if (choice == 5) createRoom();
        else if (choice == 6) viewRooms();
        else if (choice == 7) assignRoom();
        else if (choice == 8) unassignRoom();
        else if (choice == 9) break;
        else cout << "Invalid choice!" << endl;
    }
}

void studentMenu() {
    int choice;
    while (true) {
        cout << "\n=== Student Menu ===" << endl;
        cout << "1. View Profile" << endl;
        cout << "2. View My Room" << endl;
        cout << "3. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        
        if (choice == 1) viewProfile();
        else if (choice == 2) viewMyRoom();
        else if (choice == 3) break;
        else cout << "Invalid choice!" << endl;
    }
}

int main() {
    initializeSystem();
    loadStudents();
    loadRooms();
    
    cout << "\n=== Hostel Management System ===" << endl;
    
    while (true) {
        if (loginUser()) {
            // If student logged in, set their roll number
            if (loggedRole == 2) {
                loggedRollNo = getRollNumberByName(loggedUsername);
            }
            
            if (loggedRole == 0) superAdminMenu();
            else if (loggedRole == 1) managerMenu();
            else if (loggedRole == 2) studentMenu();
        }
        
        int choice = 0;
        while (choice != 1 && choice != 2) {
            cout << "\n1. Login Again" << endl;
            cout << "2. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore(1000, '\n');
            
            if (choice != 1 && choice != 2) {
                cout << "Invalid choice! Enter 1 or 2" << endl;
                choice = 0;
            }
        }
        if (choice == 2) break;
    }
    
    cout << "Thank you for using Hostel Management System!" << endl;
    return 0;
}