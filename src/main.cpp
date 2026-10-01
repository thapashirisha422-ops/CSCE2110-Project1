#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"
#include "waitinglist.h"
#include "CancellationHistory.h"

using namespace std;

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
        cout << "5. View Waiting List" << endl;
        cout << "6. Process Next Waiting Student" << endl;
        cout << "7. Undo Cancellation" << endl;
        cout << "8. View Cancellation History" << endl;
        cout << "9. Resource Utilization Report" << endl;
        cout << "10. Most Requested Resource Report" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "Invalid choice. Please enter a number from 1 to 11." << endl;
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
            for(Resource& res : resources){
                if(res.getResourceID() == cancelledReservation.getResourceID()){
                    res.setAvailabilityStatus("Available");
                    break;
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
        manager.displayReservations();
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
           manager.displayResourceUtilization();
    }
    else if (choice == 10)
    {
        manager.displayMostRequestedResource();
    }
    else if (choice == 11)
    {
        cout << "Exiting program. " << endl;
    }
    else
    {
        cout << "Invalid choice.Please try again." << endl;
    }

} while (choice != 11);   

return 0;
}
