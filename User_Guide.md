Campus Resource Reservation System - User Guide
Course : CSCE 2110 - Project 1

## How to run :
Open a terminal in the project folder.
Compile : g++ -std=c++17 -Iinclude src/*.cpp -o project1
Run : ./project1

## Menu Options
1. View Resources - Display all resources and their availability.
2. Create Reservation - Enter reservation ID, student details, resource ID and date.
3. Cancel Reservation -  Cancel an existing reservation using its ID.
4. Active Reservations Report - Display and count active reservations.
5. View Waiting List - View students waiting for resources.
6. Process next Waiting Student - Process a waiting request for a selected resource.
7. Undo Cancellation - Attempt to restore the most recent cancelled reservation.
8. View Cancellation History - Display Cancelled reservations.
9. Resource Utilization Report - Show reservation counts for every resource.
10. Most Requested Resource Report - Identify the resource with most requests.
11. Search Reservation - Find a reservation using its ID.
12. Sort Resources by Name - Arrange resources alphabetically.
13. Waiting-List Statistics Report - Show waiting student counts for every resource.
14. Exit - Close the program.

## How Reservations work:
Select option 2 to create a reservation.
Enter a valid resource ID and a date in YYYY-MM-DD format.
If the resource is unavailable, the request is added to the waiting list.
When a reservation is cancelled, the system can automatically assign the resource to the next waiting student.
Use option 11 to search for an existing reservation.

## Error Handling
The program checks invalid menu selections, duplicate reservation IDs, invalid resource IDs, and invalid dates. It also handles waiting lists and cancellation history.

## GitHub Repository
https://github.com/thapashirisha422-ops/CSCE2110-Project1


