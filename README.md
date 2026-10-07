# CSCE2110-Project1
Campus Resource Reservation System-Project 1

## Course 
CSCE 2110 - Project 1

## Description
This project is a Campus Resource Reservation

The system allows users to:
-View resource
-Create reservations
-Cancel reservations
-Search reservations/resources
-Manage waiting lists
-Undo Cancellation
-Generate reports
Sort and search system data


## Project Structure
-'src/' - c++ implementation files
-'include/' - Header files
-'data/' - Resource and reservation data file
'README.md' - Project documentation

## Compilation instructions
The project uses header files stored inside the 'include' directory.

Compile using:
'''bash
g++ -std=c++17 -Iinclude src/*.cpp -o project1

