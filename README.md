# 🗺️ Tourist Management System

> A console-based C++ application for planning trips across Pakistan — featuring city distance calculation, hotel booking, transport booking, and user authentication.
---

## 📌 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Concepts & Technologies](#concepts--technologies)
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

## License

This project was submitted as part of **CS-110 coursework at NUST**. All rights reserved by the team members.
