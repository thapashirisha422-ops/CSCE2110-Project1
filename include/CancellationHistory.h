#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"
#include <stack>

using namespace std;

class CancellationHistory
{
private:
  stack <Reservation> cancelledReservations;
public:
  void storeCancelledReservation (Reservation reservation);
  bool restoreLastCancelled(Reservation& reservation);
  void displayCancellationHistory() const;
};

#endif



