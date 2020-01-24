#ifndef STUDENT_RECORD_H
#define STUDENT_RECORD_H

#include<string>
using namespace std;
// creating struct for StudentRecord
namespace rhldee001 {
    struct StudentRecord {
        string name;
        string surname;
        string studentNumber;
        string classRecord;

        StudentRecord (string n, string s, string sn, string cr);
        
    };
}

#endif
