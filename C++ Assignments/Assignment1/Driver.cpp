// Rahul Deeljore
// Assignment 1 25/02/19


#include <iostream>
#include <cstdlib>
#include "Database.h"

using namespace std;

namespace rhldee001
{
void clear(void)
{
system("clear");
}

}
int main()
{


for(;;)
{

//Showing options and prompting user for input

cout<<"1. Add student"<<endl;
cout<<"2. Read database"<<endl;
cout<<"3. Save database"<<endl;
cout<<"4. Display given student data"<<endl;
cout<<"5. Grade student"<<endl;
cout<<"q. Quit"<<endl;
cout<<"Enter a number (or q to quit) and press return"<<endl;
string choice = "";
getline(cin, choice);
rhldee001::clear();


if (choice == "1")
{
//cout<<"number 1 choosen"<<endl;
rhldee001::addStudent();

// add student method
}

else if (choice == "2")
{
rhldee001::readDatabase();

//cout<<"number 2 choosen"<<endl;
// Read database method 
}

else if (choice == "3")
{
rhldee001::saveDatabase();

//cout<<"number 3 choosen"<<endl;
// Save database method
}

else if ( choice == "4")
{
rhldee001::displayStudent();
//cout<<"number 4 choosen"<<endl;
// Display method 
}



else if (choice =="5")
{
rhldee001::gradeStudent();
//cout<<"number 5 choosen"<<endl;
// grading method 
}

else if ( choice == "q")
{
//cout<<" q choosen"<<endl;

// exit method
break;
rhldee001::clear();
}

else
{
cout<<"Invalid input"<<endl;
}

}

return 0;

}





