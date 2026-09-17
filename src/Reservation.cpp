#include "Reservation.h"
#include <iostream>

using namespace std;

Reservation: :Reservation()
{
reservationID = "";
studentID = "";
studentName = "";
resourceID = "";
reservationDate = "";
}

Reservation: :Reservation(string rID, string sID, string name, string resID, string date)
{
    reservationID = rID;
    studentID = sID;
    studentName = name;
    resourceID = resID;
    reservationDate = date;
}

string Reservation: :getReservationID() const
{
    return reservationID;
}

string Reservation: :getStudentID() const
{
    return studentID;
}

string Reservation: :getStudentName() const
{
    return studentName;
}

string Reservation: :getResourceID() const
{
    return resourceID;
}

string Reservation: :getReservationDate() const
{
    return reservationDate;
}

void Reservation: :display() const
{
 cout << "Reservation ID: " << reservationID << endl;
 cout << "Student ID: " << studentID << endl;
 cout << "Student Name: " << studentName << endl;
 cout << "Resource ID: " << resourceID << endl;
 cout << "Reservation Date: " << reservationDate << endl;
 cout <<"------------------------" <<endl;
}

