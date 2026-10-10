#ifndef WAITINGLIST_H
#define WAITINGLIST_H

#include <string>
#include <iostream>

using namespace std;

struct WaitNode {
    string reservationID;
    string studentID;
    string studentName;
    string resourceID;
    string date;
    WaitNode* next;
};

class WaitingList {
    private:
        WaitNode* front;
        WaitNode* rear;
    
    public:
        WaitingList();
        ~WaitingList();

        void addStudent(string reservationID, string studentID, string studentName, string resourceID, string date);
        bool getNextStudentForResource(string resourceID, string& reservationID, string& studentID, string& studentName,string& date);
        
        void removeStudent();
        void displayWaitingList() const;
        bool isEmpty() const;
        bool getNextStudent(string resourceID, string& studentID);
        int getWaitCountForResource(string resourceID) const;
        bool reservationIDExists( const string& reservationID) const;
};

#endif
