#include <fstream>  // Needed for file stream objects
#include <iostream> // Needed for console stream objects
#include <sstream>  // Needed for string stream objects
#include <string>   // Needed for strings
#include <vector>   // Needed for the vector container

// Attached is a file menu.txt. Each line contains
// the Description of a food item, it's Price and
// the number of Calories contained in said dish.

// Your task is to parse this file and display
// the Description, Price and Calories on
// separate lines on standard output.

// Example
//
// INPUT:
//  Turbacon R1000.00 79046
//
// OUTPUT:
//  Turbacon
//   - R1000.00
//   - 79046 calories

// Use file streams to read in lines from the file
// into a string variable. Then use string streams
// to tokenize each word on the line. You may need
// to use a container in this tut.

// Pull in class and variables from the standard namespace
using namespace std;

int main(int argc, char * argv[])
{
	string filename = "menu.txt";
  string delimiter = " ";
	// Open file with a file stream. ifstream constructor
	// wants a C char * string, so call c_str() method.
	vector<string> items;
	ifstream in(filename.c_str());
	string line;
	while (getline(in, line)){
	  items.push_back(line);
	  
	  istringstream iss(line);
	  vector<string> items2;
	  
	  
	  do
	  {
	    string s;
	    iss >> s;
	    if(s != " "){
	      items2.push_back(s);
	    }
	      
	  } while (iss);

	  
	  for(int h=0;h<items2.size()-3;h++)
	  {
	    cout << items2[h] << " ";}
	  
	  cout << " \n";
	  cout << " - " <<items2[items2.size()-3] << "\n";
	  cout << " - " <<items2[items2.size()-2] << " Calories \n";
	  
	  
	  
	  
	
	//text += line + '\n';
	
	

	
	//string s;
	//while (!cin.eof()) {
	  //cin >> s >> ws;
	 // items.push_back(s);
	}
	


	//if(!in)
		//{ cout << "Couldn't open " << filename << endl; }

	// Close file
	in.close();

	return 0;
}
