# CSCE2110-Project1
Campus Resource Reservation System-Project 1

## Course 
CSCE 2110 - Project 1

## Description
The Campus Resource ReservationSystem is a C++ console-based application developed for CSCE 2110 Project 1. It allows the users to manage campus resources and student reservations. 

The system allows users to:
-View resource
-Create reservations
-Cancel reservations
-Search reservations/resources
-Manage waiting lists
-Undo Cancellation
-Generate reports
-Sort and search system data


## Project Structure
-'src/' - c++ implementation files
-'include/' - Header files
-'data/' - Resource and reservation data file
'README.md' - Project documentation

## Compilation instructions
The project uses header files stored inside the 'include' directory.

Compile using:
g++ -std=c++17 -Iinclude src/*.cpp -o project1

## Run Instructions
./project1

## Error Handling
The program checks invalid menu selections, duplicate reservation IDs, invalid resource IDs, and invalid dates. It also handles waiting lists and cancellation history.

## GitHub Repository
https://github.com/thapashirisha422-ops/CSCE2110-Project1

