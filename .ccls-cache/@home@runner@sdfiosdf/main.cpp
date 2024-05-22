#include <iostream>
#include <memory>
#include <math.h>
#include <vector>
#include <algorithm>


using namespace std;

int main() {
 vector<string> temp = {"a", "b", "c", "d", "g", "e"};
  for(int i = 0; i < temp.size(); i++) {
    cout << temp[i] << endl;
  }

  auto index = find(temp.begin(), temp.end(), "e");


  
  cout << "-------------------" << endl;
  temp.erase(temp.begin() + 4);
  for(int i = 0; i < temp.size(); i++) {
    cout << temp[i] << endl;
  }
  
}