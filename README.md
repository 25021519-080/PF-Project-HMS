# Hostel Management System

A C++ application for managing hostel operations including student admission, room assignment, and management.

**Language:** C++ (Standard Library)  
**Architecture:** Modular header-based design

---

## Features

- **Role-based Access Control** - 3 user roles with different permissions
- **Student Management** - Admit, view, and remove students
- **Room Management** - Create rooms and assign students (max 4 per room)
- **User Authentication** - Login system with password setup on first login

---

## User Roles

| Role | Permissions |
|------|-------------|
| **Super Admin (0)** | Full system access - Create users, manage all operations |
| **Manager (1)** | Student and room management - Admit students, assign rooms |
| **Student (2)** | Self-service - View profile and room assignment |

---

## Files

| File | Purpose |
|------|---------|
| `data.h` | Global data structures and variables |
| `roles.h` | Authentication and user management |
| `students.h` | Student admission and management |
| `rooms.h` | Room creation and assignments |
| `main.cpp` | Menu system and program flow |

---

## Data Structures

- **User** - username, password, role
- **Student** - username, fullName, rollNo, degree, semester, room
- **Room** - roomNumber, occupancy, student1, student2, student3, student4

---

## Quick Start

### Compilation
```bash
g++ -o hostel_management main.cpp
```

### Running
```bash
./hostel_management
```

### Default Admin
- **Username:** admin
- **Password:** admin123

### First Time
1. Login as admin
2. Create manager accounts
3. Admit students
4. Assign rooms

---

## Data Persistence

All data is stored in text files:
- `user.txt` - User accounts
- `students.txt` - Student records
- `rooms.txt` - Room assignments

---

## System Limits

| Item | Maximum |
|------|---------|
| Users | 150 |
| Students | 120 |
| Rooms | 30 |
