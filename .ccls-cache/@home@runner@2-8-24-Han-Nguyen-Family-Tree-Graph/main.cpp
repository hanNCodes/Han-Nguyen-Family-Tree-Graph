#include "familyTree.h"
using namespace std;


int main() {
  //object
  familyTree fam;

  //loop menu
  while(true) {

    //get user input
    int input;
    cout << "\n\nMenu:\n1) Add Family Member\n2) Delete Family Member\n3) Edit Family Member\n4) Print Family Tree\n5) Exit\nInput option number: ";
    cin >> input;
    cout << endl;
      //input 1
      if(input == 1) {
        fam.addFamilyMember();

      //input 2
      } else if (input == 2) {
          fam.deleteFamilyMember();
      //input 3
      } else if (input == 3) {
        fam.editFamilyMember();
      //input 4
      } else if (input == 4) {
        fam.printFamilyTree();

      //exit
      } else if (input == 5) {
        break;
      } 

  }

}


