#include "ReservationManager.h"
#include <iostream>
#include <map>
#include <string>
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
void ReservationManager::displayResourceUtilization() const {
    cout <<"\n===== RESOURCE UTILIZATION REPORT =====\n";
    
    if (head == nullptr) {
        cout << "No active reservations found.\n";
        return;
    }
    map<string, int> resourceCount;

    Node* current = head;

    while (current != nullptr) {
        string resourceID = current->reservation.getResourceID();

        resourceCount [resourceID]++;
        current = current->next;
    }

    int totalReservations = 0;

    for (const auto& resource : resourceCount) {
        cout << "Resource ID: "
             << resource.first
             << "| Active Reservations: "
             << resource.second
             << endl;
        
        totalReservations += resource.second;
    }

    cout << "\nTotal Active Reservations: "
         << totalReservations << endl;
}
void ReservationManager::displayMostRequestedResource() const{
    cout << "\n===== MOST REQUESTED RESOURCE REPORT =====\n";

    if (head == nullptr) {
        cout << "No reservation data available.\n";
        return;

    }
    map<string, int> resourceCount;
    Node* current = head;
    while (current != nullptr) {
        string resourceID = current->reservation.getResourceID();
        resourceCount[resourceID]++;
        current = current->next;
    }

    string mostRequestedResource;
    int highestCount = 0;

    for (const auto& resource : resourceCount){
        if (resource.second > highestCount) {
            highestCount = resource.second;
            mostRequestedResource = resource.first;
        }
    }
    cout << "Resource ID: " <<mostRequestedResource << endl;
    cout << "Number of Requests: " << highestCount << endl;

}