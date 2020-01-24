#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;

bool done = false; // boolean to see if recalculated centroids are the same
void calculateCentroids(vector<int*> points, vector<double*> centroids){
   
   int checker = 0; 
   for (int i = 0; i < centroids.size(); ++i){
      int Totalx = 0;
      int Totaly = 0;
      int numPts = 0;
      for (int j = 0; j < points.size(); ++j){ //how many points in that cluster
         if (points[j][2] == (i+1)){
            Totalx += points[j][0];
            Totaly += points[j][1];
            numPts ++;
            
         }
      }
    
      //new centroid coordinates
      double newx = (double)Totalx/(double)numPts;
      double newy = (double)Totaly/(double)numPts;
      
      // if centroids are same, program will be ended
      if (newx == centroids[i][0] && newy == centroids[i][1]){
         checker++;
         if (checker == 3){
            done = true;
         }
      }
      
      centroids[i][0] = newx;
      centroids[i][1] = newy;
      
   }
}


void calculateClusters(vector<int*> points, vector<double*> centroids) {
 
   for (int i = 0; i < points.size(); ++i){
      double shortestDist = 100; //max distance of separation for this specific case
      int closestCentroid;
      for (int j = 0; j < centroids.size(); ++j){
         double dist = sqrt(pow((centroids[j][0] - points[i][0]),2)    +    pow((centroids[j][1] - points[i][1]),2)); // distance between point and centroid
     
         if (dist < shortestDist){ //assign closest centroid
            shortestDist = dist;
            closestCentroid = j;
         }
      }
     
      points[i][2] = closestCentroid + 1;// assign centroid number in point array
   }
   

   // open output file and print values
   ofstream outputFile;
   outputFile.open("outputFile.txt", ofstream::app);
   
  
   string Cluster1 = "Cluster 1: ";
   for(int i = 0; i < points.size(); ++i){
     
      if(points[i][2] == 1){
         Cluster1 += to_string((i+1)) + " ";// if point in that cluster, print 
      }
   }
   outputFile << Cluster1 << endl;
   outputFile << "Centroid (" << centroids[0][0] << "," << centroids[0][1] << ")\n"<<endl;
   
   string Cluster2 = "Cluster 2: ";
   for(int i = 0; i < points.size(); ++i){
     
      if(points[i][2] == 2){
         Cluster2 += to_string((i+1)) + " ";
      }
   }
   outputFile << Cluster2 << endl;
   outputFile << "Centroid (" << centroids[1][0] << "," << centroids[1][1] << ")\n"<<endl;

   string Cluster3 = "Cluster 3: ";
   for(int i = 0; i < points.size(); ++i){
     
      if(points[i][2] == 3){
         Cluster3 += to_string((i+1)) + " ";
      }
   }
   outputFile << Cluster3 << endl;
   outputFile << "Centroid (" << centroids[2][0] << "," << centroids[2][1] << ") \n"<<endl;
   outputFile.close();
   
   calculateCentroids(points, centroids);
   
}

//Main
int main () {
   

  
   vector<int*> points = vector<int*>();
   vector<double*> centroids = vector<double*>();
  
   double centroid1[2] = {2,10};
   double centroid2[2] = {5,8};
   double centroid3[2] = {1,2};
   
   centroids.push_back(centroid1);
   centroids.push_back(centroid2);
   centroids.push_back(centroid3);
   
   //points - last value is centroid it belongs to
   int pt1[3] = {2,10,0};
   int pt2[3] = {2,5,0};
   int pt3[3] = {8,4,0};
   int pt4[3] = {5,8,0};
   int pt5[3] = {7,5,0};
   int pt6[3] = {6,4,0};
   int pt7[3] = {1,2,0};
   int pt8[3] = {4,9,0};
   
   points.push_back(pt1);
   points.push_back(pt2);
   points.push_back(pt3);
   points.push_back(pt4);
   points.push_back(pt5);
   points.push_back(pt6);
   points.push_back(pt7);
   points.push_back(pt8);
   
   
   int iteration = 1;
   while (!done){
      ofstream outputFile;
      outputFile.open("outputFile.txt", ofstream::app); 
      outputFile << "\nIteration " << iteration << "\n" << endl;
      outputFile.close();
      calculateClusters(points, centroids);
      iteration++;
   }
   cout<<"Calculations done. Check output file."<<endl;
   return 0;
}
