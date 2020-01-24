#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;



double value_s (double y, double r, double current_value) {
  double ans = y*current_value + r;
  return ans;
}

void value_iteration(vector < pair<double,vector<int> > > states) {
  int count = 1;
  int iteration_counter = 1;
  while (count > 0) {
    cout << "Iteration " << iteration_counter << ":" << endl;
    count = 0;
    for (int i = 0; i < states.size(); i++) {
      for (int j = 0; j < states[i].second.size(); j++) {
        double r = 0.0f;
        // reward is 100 for s6->s3
        if (i == 5 && states[i].second[j] == -3) {
          r = 100;
        }
        // reward is 50 for s2->s3
        if (i == 1 && states[i].second[j] == 1) {
          r = 50;
        }
        int direction = (states[i].second[j]);
        double s_val = value_s(0.8f, r, states[i+direction].first);
        // if new value > current, then update
        if (s_val > states[i].first) {
          states[i].first = s_val;
          count++;
        }
      }
    }

    // print out grid
    for (int i = 0; i < 2; i++) {
      for (int j = 0 + i*3; j < 3 + i*3; j++) {
        cout << "| ";
        cout << setw(4) << states[j].first;
        cout << " |";
      }
      cout << endl << "========================" << endl;
    }
    iteration_counter++;
  }
}


int main () {

  double y = 0.8f; // discount factor

  /*
     -3 -> UP
      1 -> RIGHT
      3 -> DOWN
     -1 -> LEFT
  */

  // set state directions
  vector <int> s1_dir = {3,1};
  vector <int> s2_dir = {-1,3,1};
  vector <int> s3_dir = {0};  // terminal state
  vector <int> s4_dir = {-3,1};
  vector <int> s5_dir = {-1,-3,1};
  vector <int> s6_dir = {-1,-3};

  // initial state values paired with directions
  pair< double , vector<int> > s1(0.0f,s1_dir);
  pair< double , vector<int> > s2(0.0f,s2_dir);
  pair< double , vector<int> > s3(0.0f,s3_dir);
  pair< double , vector<int> > s4(0.0f,s4_dir);
  pair< double , vector<int> > s5(0.0f,s5_dir);
  pair< double , vector<int> > s6(0.0f,s6_dir);

  vector < pair<double,vector<int> > > states;

  states.push_back(s1);
  states.push_back(s2);
  states.push_back(s3);
  states.push_back(s4);
  states.push_back(s5);
  states.push_back(s6);

  cout << "Initial grid:" << endl;
  for (int i = 0; i < 2; i++) {
    for (int j = 0 + i*3; j < 3 + i*3; j++) {
      cout << "| ";
      cout << setw(4) << states[j].first;
      cout << " |";
    }
    cout << endl << "========================" << endl;
     
  }
  cout << endl;

  value_iteration(states);




}