#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"

using namespace std;

int main()
{
    vector<Resource> resources;
    ReservationManager manager;

    //Read resources.txt
    ifstream resourceFile("data/resources.txt");

    if (!resourceFile.is_open())
    {
        cout << "Could not open resources.txt" << endl;
        return 1;
    }
    
    string line;

    while (getline(resourceFile, line))
    {
        string id;
        string name;
        string type;
        string status;

        stringstream ss(line);

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status);

        Resource resource(id, name, type, status);
        resources.push_back(resource);
    }

    resourceFile.close();

    //Read reservations.txt
    ifstream reservationFile("data/reservations.txt");

    if (!reservationFile.is_open())
    {
        cout << "Could not open reservations.txt" << endl;
        return 1;
    }
    
    while (getline(reservationFile, line))
    {
        if (line.empty())
        {
            continue;
        }
     
        string reservationID;
        string studentID;
        string studentName;
        string resourceID;
        string date;

        stringstream ss(line);

        getline(ss, reservationID, '|');
        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceID, '|');
        getline(ss, date);

        Reservation reservation(
            reservationID,
            studentID,
            studentName,
            resourceID,
            date
        );

        manager.addReservation(reservation);
    }

    reservationFile.close();

    int choice;

    do
    {
        cout << "\n===== Campus Resource Reservation System =====" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. View Active Reservations" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        if (choice ==1)
        {
            for (const Resource& resource : resources)
            {
                resource.display();
            }
        }

        else if (choice ==2)
        {
            string reservationID;
            string studentID;
            string studentName;
            string resourceID;
            string date;

            cin.ignore();

            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);

            if (manager.reservationExists(reservationID))
            {
                cout << "Reservation ID already exists." << endl;
            }
            else
            {

            cout << "Enter Student ID: ";
            getline(cin, studentID);

            cout << "Enter Student Name: ";
            getline(cin, studentName);

            cout << "Enter Resource ID: ";
            getline(cin, resourceID);

            cout << "Enter Reservation Date: ";
            getline(cin, date);

            bool resourceFound = false;
            bool resourceAvailable = false;

            for (Resource& resource : resources)
            {
                if (resource.getResourceID() == resourceID)
                {
                    resourceFound = true;

                    if (resource.getAvailabilityStatus() == "Available")
                    {
                        resourceAvailable = true;
             }
                }
            }
        
            if (!resourceFound)
            {
                cout << "Invalid Resource ID." << endl;
            }
            else if (!resourceAvailable)
            {
                cout << "Resource is unavailable." << endl;
            }
            else
            {
                Reservation newReservation(
                    reservationID,
                    studentID,
                    studentName,
                    resourceID,
                    date
                );

                manager.addReservation(newReservation);

                cout << "Reservation created successfully." << endl;
            }
        }
    }

    else if (choice == 3)
    {
        string reservationID;
        
        cin.ignore();

        cout << "Enter Reservation ID to cancel: ";
        getline(cin, reservationID);
        
    if (manager.removeReservation(reservationID))
        {
            cout << "Reservation cancelled successfully." << endl;
        }
        else
        {
            cout << "Reservation not found." << endl;
        }
    }
    else if (choice == 4)
    {
        manager.displayReservations();
    }
    else if (choice == 5)
    {
        cout << "Exiting program." << endl;
    }

} while (choice != 5);   

return 0;
}