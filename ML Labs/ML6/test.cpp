#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include <algorithm>

using namespace std;

void training(vector<int*> trainingData, double * weights, double theta, double learningRate){
   cout << "Training data.\n" << endl;
   
   int output;
   int errors = 1;// initial val at start
   double xwSum; 
   int iterations = 0;
   while (errors > 0){
      errors = 0;
      iterations++;
      for (int i = 0; i < trainingData.size(); ++i){
         xwSum = trainingData[i][0] * weights[i] + trainingData[i][1] * weights[i];
         if (xwSum > theta){
            output = 1; //Positive output
         } else {
            output = 0; // Negative output
         }
         if (output == trainingData[i][2]){
            cout << "Set " << (i+1) << " has already been learnt" << endl;
         } else {
            errors++;
           
            cout << "Learning set " << (i+1) << endl;
            weights[i] = weights[i] + (learningRate * (trainingData[i][2] - output) * xwSum); // change weights
            
         
         }
         
      }
      cout << "\nNumber of errors = " << errors << "\n" << endl;
      cout << "Weights: " << endl;
      for (int i = 0; i < 4; ++i){
         cout << weights[i] << ", ";
      }
      cout << "\n" << endl;
      
      
   }
   
   
}

int main (int argc, char *argv[]) { 
   cout << "Learning XOR." << endl;
   
   double theta = 0.5;
   double learningRate = 0.6;
   
   vector<int*> trainingData = vector<int*>();
   
   //AND 
   int data1[3] = {0, 0, 0};
   int data2[3] = {0, 1, 0};
   int data3[3] = {1, 0, 0};
   int data4[3] = {1, 1, 1};

   //OR
   int data5[3] = {0, 0, 0};
   int data6[3] = {0, 1, 1};
   int data7[3] = {1, 0, 1};
   int data8[3] = {1, 1, 1};
   
   //XOR
   
   int data9[3] =  {0, 0, 0};
   int data10[3] = {1, 0, 1};
   int data11[3] = {0, 1, 1};
   int data12[3] = {1, 1, 0};
   
   

   trainingData.push_back(data1);
   trainingData.push_back(data2);
   trainingData.push_back(data3);
   trainingData.push_back(data4);
   
   double weights[4] = {1,1,1,1};
   cout << "Input Data teaching AND:\n0,0,0\n0,1,0\n1,0,0\n1,1,1" << endl;
   training(trainingData, weights, theta, learningRate);
   
   trainingData.clear();
   trainingData.push_back(data5);
   trainingData.push_back(data6);
   trainingData.push_back(data7);
   trainingData.push_back(data8);
   
   cout << "Input Data teaching OR:\n0,0,0\n0,1,1\n1,0,1\n1,1,1\n" << endl;
   training(trainingData, weights, theta, learningRate);
   
   trainingData.clear();
   trainingData.push_back(data9);
   trainingData.push_back(data10);
   trainingData.push_back(data11);
   trainingData.push_back(data12);
   
   cout << "Input Data teaching XOR:\n0,0,0\n1,0,1\n0,1,1\n1,1,1\n" << endl;
   training(trainingData, weights, theta, learningRate);
   return 0;
   
}