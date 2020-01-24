#include "Database.h"
#include <iostream>
#include <fstream>
#include <sstream>

vector<rhldee001::StudentRecord> records;

// method to add student to database
// user is prompted for input 
void rhldee001::addStudent () {
    
    string name, surname, studentNumber1, classRecord;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter surname: ";
    getline(cin, surname);
    cout << "Enter student number: ";
    getline(cin, studentNumber1);
    cout << "Enter the student record: ";
    getline(cin, classRecord);


bool exists = false; // used to check for duplicate in database
int pos;



for(unsigned int i = 0;i < records.size(); i++)
{
if(records[i].studentNumber.compare(studentNumber1) ==0) //if student with same student number is found in database, it is overwriteen
{
exists = true;
pos = i;
}
}

if(exists == true)
{
cout<<"This student already exists in the database.Data has been overwritten."<<endl;
records.at(pos).name = name;
records.at(pos).surname = surname;
records.at(pos).classRecord = classRecord;
}

else
{
rhldee001::StudentRecord Newrec = rhldee001::StudentRecord(name, surname, studentNumber1, classRecord);

records.push_back(Newrec);// if student isnt in database, a new record is created
cout<<"The student had been added to the database."<<endl;
}

}

void rhldee001::readDatabase () {
    // Open file
    ifstream in;
    in.open("data.txt");

    
    if (!in.is_open()) {
        cout << "The file data.txt does not exist in this directory." << endl;
        return;
    }

    records.clear();// delete all existing records
    string line;
    while(getline(in, line)) {
        stringstream ss;
    string name, surname, studentNumber, classRecord;
    ss << line;
    ss >> name >> surname >> studentNumber;// first 3 values are for name, surname and student number

    
    classRecord = "";
    string mark;
    while(ss >> mark) {
        classRecord = classRecord + mark + " "; // remaining values are for class marks
    }
    classRecord = classRecord.substr(0, classRecord.length() - 1);

   
    rhldee001::StudentRecord record = rhldee001::StudentRecord(name, surname, studentNumber, classRecord);
        records.push_back(record); // repopulate with file values
    }

    in.close();
    cout << "The database has been read." << endl;
}


void rhldee001::saveDatabase () {
    //open file to write 
    ofstream out;
    out.open("data.txt", ofstream::out | ofstream::trunc);

    
    for (vector<rhldee001::StudentRecord>::iterator it = records.begin(); it != records.end(); it++) {
        out << (*it).name << " " << (*it).surname << " " << (*it).studentNumber << " " << (*it).classRecord << endl; // Add all details on one line separated by space
    }
    out.close();
    cout << "The database has overwritten." << endl;
}

void rhldee001::displayStudent () {
    // Get student number
    cout << "Enter student number: ";
    string studentNumber;
    getline(cin, studentNumber);

    // Find student in records
    for (vector<rhldee001::StudentRecord>::iterator it = records.begin(); it != records.end(); it++) {
        if ((*it).studentNumber == studentNumber) { // if found, details are printed
            
  cout   << "Name: " << (*it).name << endl;
  cout  << "Surname: " << (*it).surname << endl;
  cout << "Student Number: " << (*it).studentNumber << endl;
   cout << "Class Record: " << (*it).classRecord << endl;
            return;
        }
    }

    // Student was not found
    cout << "The student does not exist in the database." << endl;// if not found, user is prompted
}

void rhldee001::gradeStudent () {
    // Get student number
    cout << "Enter student number: ";
    string studentNumber;
    getline(cin, studentNumber);

    // Find student
    for (vector<rhldee001::StudentRecord>::iterator it = records.begin(); it != records.end(); it++) {
        if ((*it).studentNumber == studentNumber) {
         
            
          int number;
	stringstream stream1;
	stream1 << (*it).classRecord;


	int total = 0;
	int nummarks = 0;


while(stream1>>number)
{

total = total + number;
nummarks +=1;
}

int avg;
avg = total/nummarks;

cout<<"Average mark for "<< studentNumber<< " : " <<avg<<endl;
return;
}


}
        
    

    // Student was not found
    cout <<  "The student does not exist in the database." << endl;
}
