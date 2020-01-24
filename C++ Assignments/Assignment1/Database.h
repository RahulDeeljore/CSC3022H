#ifndef DATABASE_H
#define DATABASE_H

#include<vector>
#include<string>
#include "StudentRecord.h"

using namespace std;

// records exists
extern vector<rhldee001::StudentRecord> records;

//functions
namespace rhldee001 
{
void addStudent();
void readDatabase();
void saveDatabase();
void displayStudent();
void gradeStudent();
}

#endif
