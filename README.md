# Parking-Management-System

Parking Management System
Overview

The Parking Management System is a console-based application built in C++ that helps manage a parking lot efficiently. It allows users to park cars, remove cars, and purchase dedicated monthly slots. Admins can track revenue, update parking prices, and manage parking records.

This project demonstrates the use of file handling, input validation, and console UI with color-coded outputs for better user experience.

Features
User Features

Sign up / Sign in functionality

Park a vehicle (Bike, Car, SUV)

Remove a parked vehicle with automatic billing

Buy dedicated monthly parking slots

View available parking slots and rates

Admin Features

Admin login panel

View parking records

Update vehicle rates and total parking slots

View total revenue

Delete old records

Additional Features

Color-coded console interface for easy status tracking

Green: Empty slot

Red: Occupied slot

Cyan: Dedicated slot

Input validation for emails, names, and passwords

Persistent data storage using text files (users.txt, slots.txt, prices.txt, revenue.txt)

Technologies Used

C++ (File Handling, Arrays, Console I/O)

Windows Console API (for colors)

Text-based interface

Getting Started
Prerequisites

C++ compiler (e.g., GCC, Visual Studio)

Windows OS for console colors (or remove color code for cross-platform)

How to Run

Clone the repository:

git clone https://github.com/Abdullahtoqeer/parking-management-system.git


Open the project in your preferred C++ IDE.

Compile and run main.cpp.

Follow the on-screen instructions to sign up, park vehicles, and manage the parking system.

Project Structure
parking-management-system/
├── main.cpp          # Main application code
├── users.txt         # User credentials storage
├── slots.txt         # Parking slots data
├── prices.txt        # Rates and pricing
├── revenue.txt       # Total revenue tracking
└── README.md         # Project description

License

This project is open source and free to use for educational purposes
