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

    if (!resourceFiles.is_open())
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
        getline(ss, stayus);

        Resource resource(id, name, type, status);
        resources.push_back(resource);
    }

    resourceFile.close();

    //Read reservations.txt
    ifstream reservationFile("data/reservations.txt");

    if (!reservationFile,is_open())
    {
        cout << "Could not open reservations.txt" << endl;
        return 1;
    }
    
    while (getline(reservationFile, line))
    {
        string reservation ID;
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

        manager .addReservation(reservation);
    }

    reservationFile.close();

    //Display resources
    cout << '\n===== Campus Resources =====" << endl;

    for (const Resource& resource : resources)
    {
        resource.display();
    }
    
//Display reservations from linked list
cout << "\n===== Active Reservations =====" << endl;

manager.displayReservations();

return 0;
}