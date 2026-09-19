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