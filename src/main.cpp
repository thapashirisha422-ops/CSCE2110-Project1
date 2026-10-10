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
void swapResources(Resource& a, Resource& b){
    Resource temp = a;
    a = b;
    b = temp;
}
int partition(vector<Resource>& arr, int low, int high){
    string pivot = arr[high].getResourceName();
    int i = low -1;

    for(int j = low; j <= high - 1; j++){
        if(arr[j].getResourceName() < pivot){
            i++;
            swapResources(arr[i], arr[j]);
        }
    }
    swapResources(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<Resource>& arr, int low, int high){
    if(low < high){
        int part = partition(arr, low, high);
        quickSort(arr, low, part - 1);
        quickSort(arr, part + 1, high);
    }
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
      cout << "9. Resource Utilization Report" << endl;
        cout << "10. Most Requested Resource Report" << endl;
        cout << "11. Search Reservation" << endl;
        cout << "12. Sort Resources by Name" << endl;
        cout << "13. Waiting-List Statistics Report" << endl;
        cout << "14. Exit"  << endl;
      

        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

            cout << "Invalid choice. Please enter a number from 1 to 14." << endl;

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

            if (manager.reservationExists(reservationID) ||
                waitingList.reservationIDExists(reservationID))
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
                waitingList.addStudent(reservationID,studentID,studentName,resourceID,date);
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

                for(Resource& res : resources)
                {
                    if(res.getResourceID() == resourceID)
                    {
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
        if (!manager.getReservation (reservationID, cancelledReservation))
        {

            cout << "Reservation not found." << endl;
        }
        else if (manager.removeReservation(reservationID))
            {     
                cancellationHistory.storeCancelledReservation( cancelledReservation);
        
                string resourceID = cancelledReservation.getResourceID();
                if (!manager.hasReservationForResource(resourceID))
                {
                  string waitingReservationID;
                  string waitingStudentID;
                  string waitingStudentName;
                  string waitingDate;
                  if (waitingList.getNextStudentForResource(
                           resourceID,
                           waitingReservationID,
                           waitingStudentID,
                           waitingStudentName,
                           waitingDate))
                  {
                      Reservation newReservation(
                      waitingReservationID,
                      waitingStudentID,
                      waitingStudentName,
                      resourceID,
                      waitingDate
                      );
                      
                      manager.addReservation(newReservation);
                     
                    
                      cout << "Resource "
                      << resourceID
                      << ". automatically assigned to waiting student "
                      << waitingStudentID
                      << "." << endl;
                    
                  }
                }
                  for (Resource& res : resources)
                  {
                    if (res.getResourceID() == resourceID)
                    {
                      res.setAvailabilityStatus(
                        manager.hasReservationForResource(resourceID)
                            ? "Unavailable"
                            : "Available"
                        
                        );
                        break;
                    }
            }
            cout << "Reservation cancelled successfully." << endl;
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
     
        else if (choice == 6)
    {
        string resourceID;
        cout << "Enter Resource ID: ";
        cin >> resourceID;
        Resource* selectedResource = nullptr;

        for (Resource & res : resources)
            {
                if (res.getResourceID() == resourceID)
                {
                    selectedResource = &res;
                    break;
                }
            }

        if (selectedResource == nullptr)
        {
            cout << "Invalid Resource ID." << endl;
        }
            else if (manager.hasReservationForResource(resourceID) ||
                selectedResource -> getAvailabilityStatus() != "Available")
            {
                cout << "Resource is currently unavailable." << endl;
            }
                else 
            {
                string reservationID, studentID, studentName, date;
              
                if (waitingList.getNextStudentForResource(
                    resourceID, reservationID, studentID, studentName, date))
                {
                    Reservation newReservation(
                    reservationID, studentID, studentName, resourceID, date);

                    manager.addReservation(newReservation);
                    selectedResource->setAvailabilityStatus("Unavailable");

                    cout << "Resource assigned to waiting student"
                        << studentID << "." << endl;
                }
                    else
                {
                    cout << "No students waiting for this resource." << endl;
                }
            }
    }
        
        else if (choice == 7)
        {
            Reservation restoredReservation;

            if (cancellationHistory.restoreLastCancelled(restoredReservation))
            {
                if (manager.reservationExists(restoredReservation.getReservationID()))
                {
                    cout << "Reservation ID already exists." << endl;
                    cancellationHistory.storeCancelledReservation(restoredReservation);
                }
                else if (manager.hasReservationForResource(
                              restoredReservation.getResourceID()))
                {
                  cout << "Cannot restore reservation.Resource is already occupied." << endl;
                  cancellationHistory.storeCancelledReservation(restoredReservation);
                }
                else 
                {   manager.addReservation(restoredReservation);
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
            string reservationID;

            cin.ignore();

            cout << "Enter Reservation ID to search: ";
            getline(cin, reservationID);

            if (!manager.searchReservation(reservationID))
            {
                cout << "Reservation not found." << endl;
            }
        }
        else if(choice == 12){
            if (resources.empty()){
                cout << "No resources available to sort." << endl;
            }else{
                quickSort(resources, 0, resources.size() - 1);
                cout << "Resources sorted by Name!" << endl;
            }
        }else if(choice == 13){
            cout << "\n===== Waiting-List Statistics =====" << endl;
            bool anyoneWaiting = false;

            for(const Resource& res : resources){
                int waitCount = waitingList.getWaitCountForResource(res.getResourceID());
                if(waitCount > 0){
                    cout << res.getResourceName() << " (" << res.getResourceID() << "): " << waitCount << " student(S) waiting." << endl;
                    anyoneWaiting = true;
                }
            }
            if(!anyoneWaiting){
                cout << "No students currently in waiting list." << endl;
            }
        }
        else if (choice == 14)
        {
            cout << "Exiting program." << endl;
            }

    else
    {
        cout << "Invalid choice. Please try again." << endl;
    
    }
 
} while (choice !=14); 


return 0;

}
