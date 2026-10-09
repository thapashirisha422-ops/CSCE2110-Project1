#include "waitinglist.h"
#include <iostream>

using namespace std;

//setting up queue
WaitingList::WaitingList() {
    front = nullptr;
    rear = nullptr;
}

WaitingList::~WaitingList(){
    while (!isEmpty()){
        removeStudent();
    }
}

bool WaitingList::isEmpty() const{
    return front == nullptr;
}

//add new students(FIFO)
void WaitingList::addStudent(
     string reservationID, 
     string studentID,
     string studentName,
     string resourceID, 
     string date
)
{
    WaitNode* newNode = new WaitNode;
    newNode->reservationID = reservationID;
    newNode->studentID = studentID;
    newNode->studentName = studentName;
    newNode->resourceID = resourceID;
    newNode->date = date;
    newNode->next = nullptr;

    if(isEmpty())
    {
        front = newNode;
        rear = newNode;
    }else
    {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Student " << studentID
        << "added to waiting list for resource "
        << resourceID << "." << endl;
}

//Get first student waiting for a specific resource
bool WaitingList::getNextStudentForResource(
     string resourceID, 
     string& reservationID, 
     string& studentID,
     string& studentName, 
     string& date
)
{ if (isEmpty())
  {
    return false;
  }
    WaitNode* current = front;
    WaitNode* previous = nullptr;


    while (current !=nullptr)
    {
        if (current->resourceID == resourceID)
        {
            reservationID = current->reservationID;
            studentID = current->studentID;
            studentName = current->studentName;
            date = current->date;

            // Removing the first node
            if (previous == nullptr)
            {
                front = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            // If removing rear node
            if (current == rear)
            {
                rear = previous;
            }
            delete current;
            return true;

        }
        previous = current;
        current = current->next;
    }
    return false;
}

//remove student from waiting list
void WaitingList::removeStudent()
{
    if(isEmpty())
    {
        cout << "Waiting list is empty." << endl;
        return;
    }
    WaitNode* temp = front;

    front = front->next;

    if(front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
}

//display waiting list
void WaitingList::displayWaitingList() const
{
    if(isEmpty())
    {
        cout << "Waiting list is empty." << endl;
        return;
    }

    WaitNode* current = front;
    cout << "\n===== Waiting List =====" << endl;
    
    while(current != nullptr)
    {
        cout << "Reservation ID: " << current->reservationID
             << " |Student ID: " << current->studentID 
             << " |StudentName: " << current->studentName 
             << " |Resource ID: " << current->resourceID 
             << " |Date: " << current->date  
             << endl;
        current = current->next;
    }
}
//Finda and remove the first student waiting for a specific resource. 
//Returns true if a matching student is found.
bool WaitingList::getNextStudent(string resourceID, string& studentID)
{
    WaitNode* current = front;
    WaitNode* previous = nullptr;
    while (current != nullptr)
    {
        if (current->resourceID == resourceID)
        {
            studentID = current->studentID;
            // Removing the front node
            if (previous == nullptr)
            {
                front = current->next;
            }
            else 
            {
                previous->next = current->next;
            }
            //Update rear if the last node was removed
            if (current == rear)
            {    
                rear = previous;
            }
            delete current;
            return true;
           }
           previous = current;
           current = current->next;
       }
   return false;
}

int WaitingList::getWaitCountForResource(string resID) const{
    int count = 0;
    WaitNode* current = front;

    while (current != nullptr){
        if (current->resourceID == resID){
            count++;
        }
        current = current->next;
    }
    return count;
}

            

            
