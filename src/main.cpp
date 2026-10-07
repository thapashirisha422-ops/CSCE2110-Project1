#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <cctype>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "waitinglist.h"
#include "CancellationHistory.h"

using namespace std;
//Validates reservation dates in YYY-MM-DD format
bool isValidDate (const string& date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
{
    if (i == 4 || i == 7)
        continue;
    if (!isdigit (date[i]))
        return false;
}
    int year = stoi(date.substr(0,4));
    int month = stoi(date.substr(5,2));
    int day = stoi(date.substr(8,2));

    if (year < 1 || month < 1 || month > 12)
    return false;
    int daysInMonth[] =
    {31, 28, 31, 30, 31, 30,
     31, 31, 30, 31, 30, 31};
//February has 29 days during a leap year
    if (year % 400 == 0 ||
    (year % 4 == 0 && year % 100 !=0))
{
    daysInMonth[1] = 29;
}
    if (day < 1 || day > daysInMonth[month - 1])
        return false;
    return true;
}

int main()
{
    vector<Resource> resources;
    ReservationManager manager;
    WaitingList waitingList;
    CancellationHistory cancellationHistory;

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
        // A resource with an active reservation should not be available.
        for (Resource& resource : resources)
        {
            if (resource.getResourceID() == resourceID)
            {
                resource.setAvailabilityStatus("Unavailable");
                break;
            }
    }

    reservationFile.close();

    int choice;

    do
    {
        cout << "\n===== Campus Resource Reservation System =====" << endl;
        cout << "1. View Resources" << endl;
        cout << "2. Create Reservation" << endl;
        cout << "3. Cancel Reservation" << endl;
        cout << "4. Active Reservations Report" << endl;
        cout << "5. View Waiting List" << endl;
        cout << "6. Process Next Waiting Student" << endl;
        cout << "7. Undo Cancellation" << endl;
        cout << "8. View Cancellation History" << endl;
        cout << "9. Search Reservation" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid choice. Please enter a number from 1 to 10." << endl;
            continue;
        }
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

            do
                { cout << "Enter Reservation Date: ";
                getline(cin, date);
                 if (!isValidDate(date))
                 {
                     cout << "Invalid date. Please use YYYY-MM-DD format." << endl;
                 }
            } while (!isValidDate(date));

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
                cout << "Resource is unavailable. Added to waiting list." << endl;
                waitingList.addStudent(studentID, resourceID);
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

                for(Resource& res : resources){
                    if(res.getResourceID() == resourceID){
                        res.setAvailabilityStatus("Unavailable");
                        break;
                    }
                }

                cout << "Reservation created successfully." << endl;
            }
        }
    }

    else if (choice == 3)
    {
        string reservationID;
        Reservation cancelledReservation;
        
        cin.ignore();

        cout << "Enter Reservation ID to cancel: ";
        getline(cin, reservationID);
        if (manager.getReservation (reservationID, cancelledReservation))
        {
             cancellationHistory.storeCancelledReservation( cancelledReservation);
        }
       if (manager.removeReservation(reservationID))
        {
            string resourceID = cancelledReservation.getResourceID();
            //Check whether another active reservation still uses this resource.
            bool stillReserved = manager.hasReservationForResource(resourceID);

            if (stillReserved)
            {
                //Another reservation still exists, so the resource stays unavailable.
                for (Resource& res : resources)
                {
                    if (res.getResourceID() == resourceID)
                    {
                            res.setAvailabilityStatus("Unavailable");
                            break;
                    }
                }
            }
            else
            {
                string nextStudentID;
                //Give the resource to the first student waiting for it.
                if (waitingList.getNextStudent(resourceID, nextStudentID))
                {
                    //Generate an ID for the automatically created reservation.
                    string newReservationID = "AUTO_" + nextStudentID + "_" + resourceID; 

                    Reservation newReservation(
                        newReservationID,
                        nextStudentID,
                        nextStudentID,
                        resourceID,
                        cancelledReservation.getReservationDate()
                    );
                    manager.addReservation(newReservation);
                    
                 for (Resource& res : resources)
                 {
                     if (res.getResourceID() == resourceID)
                     {
                        res.setAvailabilityStatus("Unavailable");
                        break;
                     }
                 }
                cout << "Resource " << resourceID
                     << " automatically assigned to waiting student "
                     << nextStudentID << "." << endl;
            }
            else
            {
                //Nobody is waiting, so the resource becomes available.
                for (Resource& res : resources)
                    {
                        if (res.getResourceID() == resourceID)
                        { 
                            res.setAvailabilityStatus("Available");
                            break;
                        }
                    }
              }
         }
           cout << "Reservation cancelled successfully." << endl;
        }
        else
        {
            cout << "Reservation not found." << endl;
        }
    }
    else if (choice == 4)
    {
        manager.activeReservationReport();
    }
    else if (choice == 5)
    {
        waitingList.displayWaitingList();
    }
    else if (choice ==6)
    {
        waitingList.removeStudent();
    }
        else if (choice == 7)
        {
            Reservation restoredReservation;

            if (cancellationHistory.restoreLastCancelled(restoredReservation))
            {
                if (manager.reservationExists(restoredReservation.getReservationID()))
                {
                    cout << "Reservation ID already exists." << endl;
                }
                else{
                manager.addReservation(restoredReservation);
                    for(Resource& res : resources){
                        if(res.getResourceID() == restoredReservation.getResourceID()){
                            res.setAvailabilityStatus("Unavailable");
                            break;
                        }
                    }
            cout << "Reservation restored successfully." << endl;
        }
    }
        else
        {
            cout << "No cancellation history to undo." << endl;
        }
    }

        else if (choice == 8)
        {
            cancellationHistory.displayCancellationHistory();
        }
        else if (choice == 9)
        {
            string reservationID;

            cin.ignore();

            cout << "Enter Reservation ID to search: ";
            getline(cin, reservationID);

            if (!manager.searchReservation(reservationID))
            {
                cout << "Reservation not found." << endl;
            }
        }
        else if (choice == 10)
        {
            cout << "Exiting program." << endl;
            }
    else
    {
        cout << "Invalid choice. Please try again." << endl;
    }

} while (choice != 10);   


return 0;
}
