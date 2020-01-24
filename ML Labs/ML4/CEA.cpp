#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include <cstring>
#include <set>

using namespace std;

int main () {

   cout << "Starting Candidate elimination algorithm.\n"<<endl;

   int numFeatures = 6;
   vector<string> features[6]; //create an array of vectors that stores the attribute of each features
   vector<string> country = {"Japan","USA"};
   features[0]=country;
   vector<string> brand = {"Honda","Toyota","Chrysler"};
   features[1]=brand;
   vector<string> color = {"Blue","Green","Red","White",};
   features[2]=color;
   vector<string> year = {"1980","1970","1990"};
   features[3]=year;
   vector<string> type = {"Economy","Sports"};
   features[4]=type;
   vector<string> bools = {"Positive","Negative"};
   features[5]=bools;
  
   vector<string> m, n, p;
   bool consistent;

  
   vector<string*> trainingExample = vector<string*>(); //Vector of training Examples

   //Examples shown in the brief
   string Example1[6] = {"Japan", "Honda", "White", "1990", "Sports", "Positive"};   
   string Example2[6] = {"Japan", "Toyota", "Blue", "1980", "Sports", "Positive"};   
   string Example3[6] = {"Japan", "Chrysler", "Green", "1970", "Economy", "Negative"};   
   string Example4[6] = {"USA", "Toyota", "Red", "1980", "Sports", "Negative"};   
 //  string Example5[6] = {"Japan", "Honda", "White", "1980", "Economy", "Positive"};   
   //string Example6[6] = {"Japan", "Toyota", "Green", "1980", "Economy", "Positive"};   
   //string Example7[6] = {"Japan", "Honda", "Red", "1980", "Economy", "Negative"};    

   trainingExample.push_back(Example1);
   trainingExample.push_back(Example2);
   trainingExample.push_back(Example3);
   trainingExample.push_back(Example4);
  // trainingExample.push_back(Example5);
  // trainingExample.push_back(Example6);
  // trainingExample.push_back(Example7);



   
    vector<string> hypothesisStartG = {"?", "?", "?", "?", "?","?"};//initialize
    set<vector<string>> generics; //set of all generic examples that will be created
    generics.insert(hypothesisStartG); // add the initial generic to the set
    set<vector<string>> specific;

    vector<string> hypothesisStart = {"0", "0", "0", "0", "0", "0"};//initialize
    specific.insert(hypothesisStart);
  
   //print out initial hypothesis.

   cout << "h" << 0 << " = <";
   for (int i = 0; i < 5; ++i){
      cout << hypothesisStart[i] << " ";
   }
   cout << ">\n";


   cout << "h" << 0 << " = <";
   for (int i = 0; i < 5; ++i){
      cout << hypothesisStartG[i] << " ";
   }
   cout << ">\n\n";

  

  vector<string> hypothesis ={"Japan", "Honda", "White", "1990", "Sports", "Positive"};   // first example
    int exampleNumber = 0;// Number of training examples
   for (int i = 0; i < trainingExample.size(); ++i)
   {
      //cout<<i<<endl;
      //cout<<trainingExample.size()<<endl;
   bool positive = false; // used to identify only positive cases
  
     
      if (trainingExample[i][5] == "Positive")
      {// use only positive examples
       positive = true; // positive case 
       set <vector<string>> tempg;
       tempg = generics;
       for(set<vector<string> >::iterator it= generics.begin(); it!=generics.end(); it++)
        {
        m = *it;
        int er =0;
        for(int k=0; k<6; k++)
           {
          if(m[k]!=trainingExample[i][k] && m[k]!="?" )
              {
            er = 1;
            break;
              }
            }
        if(er==1)
          tempg.erase(m);
         }
      generics = tempg;
       
    
         for (int j = 0; j < 5; ++j)
         {
            
            if (hypothesis[j] == trainingExample[i][j]) //if same, do nothing
            { 
           // cout<<"same"<<endl;
            } 
            else
            {
               hypothesis[j] = "?";// if different, replace with ?
            }
           
         }

      

       exampleNumber += 1;// increase number of tranin examples by 1 since case is positive.
       cout << "h" << exampleNumber << " = <"; //Print out hypothesis
      

   for (int i = 0; i < 5; ++i){
      cout << hypothesis[i] << " ";
         }
   cout << ">\n";

   cout << "g" << exampleNumber << " = "; //Print out hypothesis
   for(set<vector<string> >::iterator it= generics.begin(); it!=generics.end(); it++)
        {
        m = *it;
        cout<<"<";
        for(int i=0;i<5;++i)
        {
           cout<<m[i]<<" ";
        }
        cout << ">\n";
        }
        cout << "\n\n";



      }//positiveend

  else //if negative example
    {
      /*
      if example is inconsistent with spec border, then it is noise
      */
      //cout<<"test1"<<endl;
      set < vector<string> > tempg, temps;
      


      for(set< vector<string> >::iterator it= generics.begin(); it!=generics.end(); it++)
      {
        m = *it;

        int er=0;
        //check if given example is consistent with the present hypothesis
        for(int l=0; l<6; l++)
        {
          if( m[l]!="?" && m[l]!=trainingExample[i][l])
          {
            er=1; //curr hyp is consistent
            break;
          }
        }

        if(er==1)//if hyp is consistent with the example
        {
          tempg.insert(m);
        }
        else//hyp is not consistent with the example
        {
          vector<string> temphyp;
                //cout<<"test2"<<endl;

          for(int a=0; a<6; a++)
          {
            // cout<<m[a]<<endl;
            if( m[a]=="?" )
            {
              temphyp = m;
              //cout<<"Hey"<<endl;
              for(int b=0; b<features[a].size(); b++)//values are 1-based
              
              {   
                 //cout<<features[a].size()<<endl;
                 //cout<<features[a][b]<<endl;
                 //cout<<trainingExample[i][a]<<endl;
                if(features[a][b]==trainingExample[i][a])
                  continue;
                else
                {
                  temphyp[a] = features[a][b];
                    //check if temphyp is more general than specifc hyp.
                  consistent = true;
                  for(int k=0; k<6; k++)
                  {
                     //cout<<"Waar"<<endl;
                   //  cout<<temphyp[k]<<endl;
                     //cout<<hypothesis[k]<<endl;
                    if(temphyp[k]!="?" && temphyp[k]!=hypothesis[k] && hypothesis[k]!="0")
                    {
                      consistent = false;
                      break;
                    }
                  }
                  if(consistent)
                    tempg.insert(temphyp); // new hypo is consistent
                }
              //  cout<<"testclose1"<<endl;
              }
             // cout<<"testclose2"<<endl;
            }
           // cout<<"testclose3"<<endl;
          }
         // cout<<"testclose4"<<endl;
          
        }
       // cout<<"testclose5"<<endl;

      }
     //cout<<"testclose"<<endl;
    generics.clear();
      bool mGen;
      set<vector<string> > tempgg;
      
      //remove from generic any hyp that is more specific than another hyp in generic
      for(set< vector<string> >::iterator it= tempg.begin(); it!=tempg.end(); it++)
      {
        m = *it;

        for( set< vector<string> >::iterator jt= tempg.begin(); jt!=tempg.end(); jt++ )
        {
          if(it==jt)
            continue;

          p = *jt;
          consistent = true;
          for(int k=0; k<6; k++)
          {
            if(m[k]!="?" && m[k]!=p[k])
            {
              consistent = false;
              break;
            }
          }
          if(consistent)
            tempgg.insert(p);
        }
      }

   // generic = set_difference(tempg, tempgg );
      for( set< vector<string> >::iterator it= tempg.begin(); it!=tempg.end(); it++ )
      {
        m = *it;

        if(tempgg.find(m)==tempgg.end())
        {
          generics.insert(m);
        }
      }
      exampleNumber += 1;// increase number of tranin examples by 1 since case is positive.
       cout << "h" << exampleNumber << " = <"; //Print out hypothesis
      

   for (int i = 0; i < 5; ++i){
      cout << hypothesis[i] << " ";
         }
   cout << ">\n";

   cout << "g" << exampleNumber << " = "; //Print out hypothesis
   for(set<vector<string> >::iterator it= generics.begin(); it!=generics.end(); it++)
        {
        
        m = *it;
        cout<<"<";
        for(int i=0;i<5;++i)
        {
           
           cout<<m[i]<<" ";
      
        }
        cout << ">\n";
        }
        cout << "\n\n";


    }//negative end
  }


   //}//forloopend
  /*  for(set<vector<string> >::iterator it= generics.begin(); it!=generics.end(); it++)
        {
        m = *it;
        for(int i=0;i<5;++i)
        {
           cout<<m[i]<<" ,";
        }
        } */

   
   cout << "End." << endl;
   return 0;

}
