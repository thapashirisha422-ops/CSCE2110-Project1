#include "ReservationManager.h"
#include <iostream>

using namespace std;

ReservationManager::ReservationManager()
{
    head = nullptr;
}

ReservationManager::~ReservationManager()
{
  Node* current = head;
  
  while (current != nullptr)
  {
    Node* temp = current;
    current = current->next;
    delete temp;
  }
}

void ReservationManager::addReservation(Reservation reservation)
{
    Node* newNode = new Node(reservation);
    if (head == nullptr)
    {
        head = newNode;
    }
else
{
    Node* current = head;
    while (current->next !=nullptr)
    {
        current = current->next;
    }

    current->next = newNode;
 }    
}

bool ReservationManager::removeReservation(string reservationID)
{
    if (head ==nullptr)
    {
        return false;
    }

    if (head->reservation.getReservationID() == reservationID)
{
    Node* temp = head;
    head = head->next;
    delete temp;
    return true;
} 

Node* current = head;

while (current->next !=nullptr)
{
    if (current->next->reservation.getReservationID() == reservationID)
    {
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    current = current->next;
}
    return false;
}

bool ReservationManager::reservationExists(string reservationID) const
{
    Node* current = head;

    while (current !=nullptr)
{
    if (current->reservation.getReservationID() == reservationID)
    {
        return true;
    }
    current = current->next;
} 
   return false;
}

bool ReservationManager::getReservation(string reservationID, Reservation& reservation) const
{
    Node* current = head;

    while (current !=nullptr)
    {
        if (current->reservation.getReservationID() == reservationID)
        {
            reservation = current->reservation;
            return true;
        }
        current = current->next;
    }
    return false;
}

string ReservationManager::getResourceID(string reservationID) const
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getReservationID() == reservationID)
        {
            return current->reservation.getResourceID();
        }
        current = current->next;
    }
    return "";
}

void ReservationManager::displayReservations() const
{
    if (head == nullptr)
    {
        cout << "No active reservations." << endl;
        return;
    }

    Node* current = head;

    while (current !=nullptr)
    {
        current->reservation.display();
        current = current->next;
    }
}

bool ReservationManager::searchReservation(string reservationID) const
{
    Node* current = head;

    while (current != nullptr)
    {
        if (current->reservation.getReservationID() == reservationID)
        {
            current->reservation.display();
            return true;
        }

        current = current->next;
    }
    return false;
}

void ReservationManager::activeReservationReport() const
{
    cout << "\n===== Active Reservations Report =====" << endl;

    if (head == nullptr)
    {
        cout << "No active reservations." << endl;
        return;
    }

    Node* current = head;
    int count = 0;

    while (current != nullptr)
    {
        current->reservation.display();
        count++;
        current = current->next;
    }
    cout << "Total Active Reservations: " << count << endl;
    }
bool ReservationManager::hasReservationForResource(string resourceID) const
{
    Node* current = head;
    //Search the linked list for another reservation
    //associated with this resource.
    while (current != nullptr)
   {
        if (current-> reservation.getResourceID() == resourceID)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
