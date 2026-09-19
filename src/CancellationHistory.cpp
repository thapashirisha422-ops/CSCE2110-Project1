#include "../include/CancellationHistory.h"
#include <iostream>

using namespace std;

void CancellationHistory::storeCancelledReservation (Reservation reservation)
{
  cancelledReservations.push(reservation);
}
bool CancellationHistory::restoreLastCancelled(Reservation& reservation)
{
  if (cancelledReservations.empty())
{
  return false;
}
reservation = cancelledReservations.top();
cancelledReservations.pop();

return true;
}
void CancellationHistory::displayCancellationHistory() const
{
  if (cancelledReservations.empty())
{
    cout << "No cancellation history." << endl;
    return;
  }
 stack<Reservation> temp = cancelledReservations;
 while (!temp.empty())
  {  
    temp.top().display();
    temp.pop();
}
} 
