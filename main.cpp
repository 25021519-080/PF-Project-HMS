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
        cout << "4. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(1000, "\n");
        
        if (choice == 1) viewProfile();
        else if (choice == 2) createUser();
        else if (choice == 3) assignRole();
        else if (choice == 4) break;
        else cout << "Invalid choice!" << endl;
    }
}

int main() {
    initializeSystem();
    
    cout << "\n=== Hostel Management System ===" << endl;
    
    while (true) {
        if (loginUser()) {
            if (loggedRole == 0) superAdminMenu();
        }
        
        int choice = 0;
        while (choice != 1 && choice != 2) {
            cout << "\n1. Login Again" << endl;
            cout << "2. Exit" << endl;
            cout << "Choice: ";
            cin >> choice;
            cin.ignore(1000, "\n");
        }
        if (choice == 2) break;
    }
    
    cout << "Thank you for using Hostel Management System!" << endl;
    return 0;
}
