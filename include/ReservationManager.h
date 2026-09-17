#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H

#include "Reservation.h"
#include <string>

using namespace std;

class ReservationManager
{
private:

       struct Node
       {
        Reservation reservation;
        Node* next;

        Node (Reservation r)
        {
            reservation = r;
            next = nullptr;
        }
        };
       Node*head;

public:

       ReservationManager();
       ~ReservationManager();
       void addReservation(Reservation reservation);
       bool removeReservation( string reservationID);
       bool reservationExists( string reservationID) const;
       void displayReservations() const;
};
#endif