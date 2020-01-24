// ML lab 1


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <string>
#include <math.h>

#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

int main (int argc, char *argv[]) {
   
   double xavg;
   double yavg;

   cout << "Program Running \n";
   
  
   ifstream dataPoints;
   dataPoints.open("data.txt");
   
   vector<float> Xvals = vector<float>();
   vector<float> Yvals = vector<float>();

   string dataPoint;

   //Read from text file;
   while (getline(dataPoints, dataPoint)){
      istringstream iss(dataPoint);
      float xVal;
      iss >> xVal;
      float yVal;
      iss >> yVal;
      
      Xvals.push_back(xVal);
      Yvals.push_back(yVal);


      
}

 
for (int i = 0; i < Yvals.size(); ++i)
{
xavg = xavg + Xvals[i];
yavg = yavg + Yvals[i];

}


xavg = xavg/Xvals.size();

yavg = yavg/Yvals.size();

double Xvar;
double Yvar;

// covariance
for (int i = 0; i < Yvals.size(); ++i)
{
Xvals[i] -= xavg;

Xvar += (Xvals[i] * Xvals[i]);

Yvals[i] -= yavg;

Yvar += (Yvals[i] * Yvals[i]);
}

Xvar = Xvar/(Xvals.size()-1);
Yvar = Yvar/(Yvals.size()-1);


vector<float> covarianceSum = vector<float>(4);
   
   for (int i = 0; i < Xvals.size(); ++i){
      double val1 = Xvals[i]*Xvals[i];
      covarianceSum[0] += val1;
      double val2 = Xvals[i]*Yvals[i];
      covarianceSum[1] += val2;
      covarianceSum[2] += val2;
      double val4 = Yvals[i]*Yvals[i];
      covarianceSum[3] += val4;   
   }
   
    
   covarianceSum[0] /= (Xvals.size()-1);
   covarianceSum[1] /= (Xvals.size()-1);
   covarianceSum[2] /= (Xvals.size()-1);
   covarianceSum[3] /= (Xvals.size()-1);
 

  fstream outputFile;
  outputFile.open("Output.txt",fstream::out);
  

   double varSum = covarianceSum[0]+covarianceSum[3];  
   
   
 
   

 Matrix<float, 2, 2> covarMatrix;

  // setting matrix vertices values
  covarMatrix(0,0) = covarianceSum[0];
  covarMatrix(0,1) = covarianceSum[1];
  covarMatrix(1,0) = covarianceSum[2];
  covarMatrix(1,1) = covarianceSum[3];
 
  EigenSolver<Matrix<float,2,2>> eigen(covarMatrix);


  outputFile << "Eigenvalues:" << endl;
  outputFile << "PC 1: " << eigen.eigenvalues().real().coeff(0,0) << endl;
  outputFile << "PC 2: " << eigen.eigenvalues().real().coeff(1,1) << endl<< endl;



  outputFile << "Eigenvectors:" << endl;
  outputFile << "PC 1: "<< eigen.eigenvectors().real().coeff(0,0) <<"(Jan) "<<eigen.eigenvectors().real().coeff(0,1)<<"(July)"<< endl;
  outputFile << "PC 2: "<< eigen.eigenvectors().real().coeff(1,0) <<"(Jan) "<<eigen.eigenvectors().real().coeff(1,1)<<"(July)"<<  endl << endl;

  outputFile <<"Covariance Matrix:"<<endl;

   outputFile  << covarianceSum[0] << "  " << covarianceSum[1] << endl;
   outputFile  << covarianceSum[2] << "  " << covarianceSum[3] << endl;

  outputFile << "\nTotal Variance: " << varSum<<endl<<endl;


 double x = eigen.eigenvalues().real().coeff(0,0);
 double y = eigen.eigenvalues().real().coeff(1,1);
 
outputFile <<"PC 1 explains: "<< (x/varSum) * 100 <<"%"<<endl;
outputFile <<"PC 2 explains: "<<(y/varSum) * 100 << "%";

 outputFile.close();

cout<<"Calculations done. Check output file. \n";
return 0;









}
