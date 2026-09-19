#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation
{
private:
    string reservationID;
    string studentID;
    string studentName;
    string resourceID;
    string reservationDate;

 public:
    Reservation();

    Reservation( string rID, string sID, string name, string resID, string date);

    string getReservationID() const;
    string getStudentID() const;
    string getStudentName() const;
    string getResourceID() const;
    string getReservationDate() const;

    void display() const;
};
#endif    