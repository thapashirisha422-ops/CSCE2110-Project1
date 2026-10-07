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
void WaitingList::addStudent(string studentID, string resourceID){
    WaitNode* newNode = new WaitNode;
    newNode->studentID = studentID;
    newNode->resourceID = resourceID;
    newNode->next = nullptr;

    if(isEmpty()){
        front = newNode;
        rear = newNode;
    }else{
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Student " << studentID << " ->resource " << resourceID << endl;
}

//remove student from waiting list
void WaitingList::removeStudent(){
    if(isEmpty()){
        cout << "Waiting list is empty." << endl;
        return;
    }
    WaitNode* temp = front;

    front = front->next;

    if(front == nullptr){
        rear = nullptr;
    }
    delete temp;
}

//display waiting list
void WaitingList::displayWaitingList() const{
    if(isEmpty()){
        cout << "Waiting list is empty." << endl;
        return;
    }

    WaitNode* current = front;
    cout << "\n===== Waiting List =====" << endl;
    
    while(current != nullptr){
        cout << "Student ID: " << current->studentID << " ResourceID: " << current->resourceID << endl;
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
            studentID = current->studentID:
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
            

            
