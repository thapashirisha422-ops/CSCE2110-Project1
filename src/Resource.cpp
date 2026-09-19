#include "Resource.h"
#include <iostream>

using namespace std;

Resource::Resource()
{
    resourceID = "";
    resourceName = "";
    resourceType = "";
    availabilityStatus = "";
}
Resource::Resource(string id, string name, string type, string status)
{
resourceID = id;
resourceName = name;
resourceType = type;
availabilityStatus = status;    
}

string Resource::getResourceID() const
{
    return resourceID;
}

string Resource::getResourceName() const
{
    return resourceName;
}

string Resource::getResourceType()const
{
    return resourceType;
}

string Resource::getAvailabilityStatus() const
{
    return availabilityStatus;
}

void Resource::setAvailabilityStatus(string status)
{
    availabilityStatus = status;
}

void Resource::display() const
{
   cout << "Resource ID: " << resourceID << endl;
   cout << "Resource Name: " << resourceName << endl;
   cout << "Resource Type: " << resourceType << endl;
   cout << "Availability: " << availabilityStatus << endl;
   cout << "------------------------" << endl;
}