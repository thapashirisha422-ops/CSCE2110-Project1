#ifndef CANCELLATIONHISTORY_H
#define CANCELLATIONHISTORY_H

#include "Reservation.h"


class CancellationHistory
{
private:
  struct Node
{
  Reservation reservation;
  Node* next;

  Node(const Reservation& r, Node* n)
      : reservation(r), next(n) {}
};
Node* topNode;

public:
  CancellationHistory();
  ~CancellationHistory();

  CancellationHistory(const CancellationHistory&) = delete;
  CancellationHistory& operator = (const CancellationHistory&) = delete;

  void storeCancelledReservation (Reservation reservation);
  bool restoreLastCancelled(Reservation& reservation);
  void displayCancellationHistory() const;
};

#endif



