# 🗺️ Tourist Management System

> A console-based C++ application for planning trips across Pakistan — featuring city distance calculation, hotel booking, transport booking, and user authentication. Built as part of the CS-110 Fundamentals of Programming course at **NUST SEECS**.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Concepts & Technologies](#concepts--technologies)
- [Getting Started](#getting-started)
- [Sample Usage](#sample-usage)
- [Contributors](#contributors)
- [License](#license)

---

## Overview

The Tourist Management System helps users plan trips efficiently through an interactive console interface. Users can register, log in, explore tourist destinations across Pakistan, calculate travel distances, book hotels based on budget and preferences, and reserve transport — all without leaving the terminal.

This project was built without any external libraries, demonstrating core C++ programming concepts in a real-world application context.

---

## Features

### 🔐 User Authentication
- Sign up with a new account
- Secure login with session handling (in-memory)
- Input validation on all credential fields

### 📏 Tour Distance Calculator
- Select tourist locations by category:
  - Historical · Urban · Modern · Rural · Northern Areas
- Calculates distance between locations using the **Haversine Formula**
- Covers all major cities of Pakistan

### 🏨 Hotel Booking System
- Filter hotels by **city**, **budget**, and **star rating**
- Room types: Standard · Deluxe · Suite
- Meal plan options included
- Automatic bill calculation in both **USD** and **PKR**
- Booking history saved to `bookings.txt`

### 🚌 Transport Booking System
- Book from: Bus · Car · Van
- Seat selection and driver assignment
- Cost calculation with service charges
- Printable invoice generation

---

## Project Structure

```
tourist-management-system/
│
├── main.cpp                  # Entry point
├── auth/
│   └── UserAuth.cpp/.h       # Sign up, login, session handling
├── calculator/
│   └── DistanceCalc.cpp/.h   # Haversine formula, city coordinates
├── hotel/
│   └── HotelBooking.cpp/.h   # Hotel filtering, billing, file I/O
├── transport/
│   └── TransportBooking.cpp/.h  # Vehicle booking, invoices
├── data/
│   └── bookings.txt          # Persistent booking records
└── README.md
```

---

## Concepts & Technologies

| Concept | Application |
|---------|-------------|
| FoCP | Classes for User, Hotel, Vehicle, Booking |
| File Handling (`fstream`) | Persistent storage of booking history |
| STL Containers | `vector` for listings, `map` for city coordinates |
| STL Algorithms | `find_if`, `transform` for filtering and search |
| Mathematical Calculations | Haversine formula for great-circle distance |
| Modular Programming | Separate modules per feature |
| Input Validation | Error handling on all user inputs |

**Language:** C++  
**Compiler:** GCC / MSVC (any standard C++17 compiler)  
**Platform:** Console Application (cross-platform)

---

## Getting Started

### Prerequisites
- A C++ compiler (GCC 9+, Clang, or MSVC)
- Terminal / Command Prompt

### Build & Run

```bash
# Clone the repository
git clone https://github.com/your-username/tourist-management-system.git
cd tourist-management-system

# Compile
g++ -std=c++17 -o tms main.cpp

# Run
./tms
```

> On Windows, replace `./tms` with `tms.exe`

---

## Sample Usage

```
==============================
   TOURIST MANAGEMENT SYSTEM
==============================
1. Sign Up
2. Login
3. Exit
Enter choice: 2

> Welcome alisha@nust.edu.pk

Main Menu:
1. Distance Calculator
2. Hotel Booking
3. Transport Booking
4. Logout

> [2] Hotel Booking
City: Lahore | Budget: PKR 10,000 | Rating: 3★
Available rooms: Standard, Deluxe
Meal plan: Yes
Total Bill: PKR 9,500 / $34 USD
Booking saved
```

---

## Contributors

| Name | Role |
|------|------|
| Alisha Maryam Habib | Core Development |
| Bismah Adil | Core Development |
| Meerab Emaan | Core Development |

---

## License

This project was submitted as part of **CS-110 coursework at NUST**. All rights reserved by the team members.
