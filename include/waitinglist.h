#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>
#include <iostream>

using namespace std;

struct WaitNode {
    string studentID;
    string resourceID;
    WaitNode* next;
};

class WaitingList {
    private:
        WaitNode* front;
        WaitNode* rear;
    
    public:
        WaitingList();
        ~WaitingList();

        void addStudent(string studentID, string resourceID);
        void removeStudent();
        void displayWaitingList() const;
        bool isEmpty() const;
};

#endif
