#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct familyMember{
  string fullName;
    string fName;
    string mName;
    string lName;
  vector<familyMember*> connectionsList;
  vector<string> connectionsName;
  int birthYear;
  string description;

};

class familyTree {
  private:
    map<string, familyMember*> familyTreeHee;
    vector<string> relations = {"Father", "Mother", "Daughter", "Son", "Cousin", "Brother", "Sister", "Niece", "Nephew", "Aunt", "Uncle", "Grandmother", "Grandfather", "Granddaughter", "Grandson", "Granddaughter", "Great Grandfather", "Great Grandmother", "Great Granddaughter", "Great Grandson"};
    bool fRunThrough = false;
  public:
    //main fucntions
      familyTree();
      void addFamilyMember();
      void editFamilyMember();
      void deleteFamilyMember();
    //helping functions
      string readLine(string);
      int readInt(string);
      string toLowerCase(string);
      void printMapNames();
      void printFamilyTree();
      void printFamilyMember(familyMember*);
      void printConnections(familyMember*);
      bool addConnections(familyMember *&, string, bool);
      bool ifFound(string);
};