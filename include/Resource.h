#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource
{
    private:
    string resourceID;
    string resourceName;
    string resourceType;
    string availabilityStatus;

public:
Resource();

Resource( string id, string name, string type, string status);

string getResourceID() const;
string getResourceName() const;
string getResourceType() const;
string getAvailabilityStatus() const;

void setAvailabilityStatus(string status);

void display() const;
};

#endif