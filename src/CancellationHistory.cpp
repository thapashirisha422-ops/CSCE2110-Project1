#include "../include/CancellationHistory.h"
#include <iostream>

using namespace std;

CancellationHistory::CancellationHistory()
{
  topNode = nullptr;
}
CancellationHistory::~CancellationHistory()
{
  while (topNode != nullptr)
 {
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
 }
}
    
void CancellationHistory::storeCancelledReservation (Reservation reservation)
{
 topNode = new Node(reservation, topNode);
}
bool CancellationHistory::restoreLastCancelled(Reservation& reservation)
{
  if (topNode == nullptr)
  {
    return false;
  }
  reservation = topNode->reservation;
  Node* temp = topNode;
  topNode = topNode->next;
  delete temp;

  return true;
}

void CancellationHistory::displayCancellationHistory() const
{
  if (topNode == nullptr)
  {
    cout << "No cancellation history." << endl;
    return;
  }
  Node* current = topNode;

  while (current != nullptr)
  {
    current->reservation.display();
    current = current->next;
  }
} 
