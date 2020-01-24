#include <iostream>
#include <string.h>

using namespace std;

void reverseStr(string& str) 
{ 
  int n = str.length(); 
  for (int i = 0; i < n / 2; i++) 
    swap(str[i], str[n - i - 1]); 
} 

int main(){

  
  
  cout<<"Enter a sentence below to check (-1 to end): "<<endl;
  string rev;
  getline(cin,rev);
 while(rev != "-1")
 {
 

  string str;
  string temp;
  str = rev;                                                     
  reverseStr(str); 
  cout << rev << " reversed is:" << " ["<<str<<"]"<<endl; 
  if (str.compare(rev) == 0)
  {
    cout << rev<<" is a palindrome"<<endl;
  }

  else
  {
    cout << rev<<" is not a palindrome"<<endl;
  }
  
  cout<<endl;
  cout<<"Enter a sentence below to check (-1 to end): "<<endl;
  getline(cin,rev);

 }
  return 0;
}