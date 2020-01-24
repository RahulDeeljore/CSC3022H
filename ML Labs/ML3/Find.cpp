#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include <cstring>

using namespace std;

int main () {

   cout << "Starting Find-S algorithm.\n"<<endl;

  
   vector<string*> trainingExample = vector<string*>(); //Vector of training Examples

   //Examples shown in the brief
   string Example1[7] = {"Sunny", "Warm", "Normal", "Strong", "Warm", "Same", "Yes"};   
   string Example2[7] = {"Sunny", "Warm", "High", "Strong", "Warm", "Same", "Yes"};
   string Example3[7] = {"Rainy", "Cold", "High", "Strong", "Warm", "Change", "No"};
   string Example4[7] = {"Sunny", "Warm", "High", "Strong", "Cool", "Change", "Yes"};

   // Additional example needed to obtain result
   string Example5[7] = {"Sunny", "Warm", "High", "Weak", "Cool", "Change", "Yes"};

   trainingExample.push_back(Example1);
   trainingExample.push_back(Example2);
   trainingExample.push_back(Example3);
   trainingExample.push_back(Example4);
   trainingExample.push_back(Example5);
   
   string hypothesisStart[6] = {"0", "0", "0", "0", "0", "0"};//initialize
  
   //print out initial hypothesis.
   cout << "h" << 0 << " = <";
   for (int i = 0; i < 6; ++i){
      cout << hypothesisStart[i] << " ";
   }
   cout << ">\n\n";
  

   string hypothesis[6] = {"Sunny", "Warm", "Normal", "Strong", "Warm", "Same"};// first example
    int exampleNumber = 0;// Number of training examples
   for (int i = 0; i < trainingExample.size(); ++i){
   bool positive = false; // used to identify only positive cases
  
     
      if (trainingExample[i][6] == "Yes"){// use only positive examples
       positive = true; // positive case 
       
        // cout << "Number of positive training examples: " << (exampleNumber +1) << endl;
           
         for (int j = 0; j < 6; ++j)
         {
            
            if (hypothesis[j] == trainingExample[i][j]) //if same, do nothing
            { 
            
            } 
            else
            {
               hypothesis[j] = "?";// if different, replace with ?
            }
           
         }
       if(positive = true)
       {
       exampleNumber += 1;// increase number of tranin examples by 1 since case is positive.
       cout << "h" << exampleNumber << " = <"; //Print out hypothesis
       positive = false;
       }
       else
       {
       cout << "h" <<  exampleNumber << " = <";
       }
   for (int i = 0; i < 6; ++i){
      cout << hypothesis[i] << " ";
   }
   cout << ">\n\n";
      }
      
   }
   
   cout << "End." << endl;
   return 0;

}
