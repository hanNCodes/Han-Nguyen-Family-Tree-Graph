#include "familyTree.h"


//----Main Functions----//

//initial lines
familyTree::familyTree() {
  cout << "Creating your family tree, beginning with you!\n";

  //add user to family tree
  familyMember* you = new familyMember();
  
  you->fullName = readLine("Please enter your full name: ");
  you->birthYear = readInt("Please enter your birth year: ");
  you->description = readLine("Please enter your description: ");
  familyTreeHee[you->fullName] = you;

  cout << "\nYou can now add to your family tree!";
}


//adds family member
void familyTree::addFamilyMember() { 
  cin.ignore();
  //add to new member
  familyMember* newMember = new familyMember();
    newMember->fullName = readLine("Enter family member's name: ");
    newMember->birthYear = readInt("Please enter " +  newMember->fullName + "'s birth year: ");
    newMember->description = readLine("Please enter " + newMember->fullName + "'s description: ");

    //adds relatives
    string prompt ="\nFrom the current family tree, which family member would you like to add as a relative to " + newMember->fullName + "?(Type 'tree' to print family tree): ";
    fRunThrough = false;

    while(true) {
      if(!addConnections(newMember, prompt, false)) {
        break;
      } else {
        if(fRunThrough) {
          prompt = "\nEnter name of another relative(press 'enter' to exit): ";
        }
      }
    }

  familyTreeHee[newMember->fullName] = newMember;
  cout << "\nNew family member added!\n";

}


void familyTree::editFamilyMember() {
  cin.ignore();
  string name;

    //loop for valid name
    while(true) {
      name = readLine("\nEnter family member's name(Type 'tree' to print family tree): ");
        if(name == "tree") {
          printFamilyTree();
          continue;
        }
        if(ifFound(name)) {
          break;
        } else {
          continue;
        }
    }
    //get fam member
    familyMember *&temp = familyTreeHee[name];

    //edit that member
    while(true) {
      
      //edit options
      int edit = readInt("\nWhat would you like to edit?:\n1) Full Name\n2) Birth Year\n3) Connections\n4) Description\n5) Exit\nInput option number: ");
      cout << endl;

      //if edit full name
      if(edit == 1) {
        string newName = readLine("Please enter new full name: ");
        temp->fullName = newName;
        cout << "\nName updated to " << newName << ".\n";

      //if edit birth year
      } else if (edit == 2) {
          int newBYear = readInt("Please enter new birth year: ");
          temp->birthYear = newBYear;
          cout << "\nBirth year updated to " << newBYear << ".\n";

      //if edit connections
      } else if (edit == 3) {
          cout << "--------\n";
          printConnections(temp);
          while(true) {
            int addOrNah = readInt("\nWould you like to:\n1) Add family member to connections\n2) Other\nInput option number: ");

              if(addOrNah == 1) {
                string prompt ="\nFrom the current family tree, which family member would you like to add as a relative to " + temp->fullName + "?(Type 'tree' to print family tree, enter to exit): ";
                addConnections(temp, prompt, true);
                return;
              } else if (addOrNah == 2) {
                  break;
              } 
          }
          //loop for valid name
          while(true) {
            string editConn = readLine("\nEnter family member's name of connection to edit(press 'enter' to exit): ");
            if(editConn == "") {
              break;
            }
            bool exist = false;
            int index = 0;

            for(int i = 0; i < temp->connectionsList.size(); i++) {
              if(temp->connectionsList[i]->fullName == editConn) {
                exist = true;
                index = i;
                break;
              }
            }

            if(exist) {
              int editConn2 = readInt("\nWhat would you like to edit?:\n1) Relation Name\n2) Delete\nInput option number(press 'enter' to exit): ");
              if(editConn2 == 1) {
                string newRelat = readLine("\nEnter " + temp->fullName + "'s relationship to " + editConn + ": ");
                temp->connectionsName[index] = newRelat;
                cout << "\nRelation updated to " << newRelat << ".\n\n";
                
              } else if (editConn2 == 2) {
                  int index2;
                  for(int i = 0; i < familyTreeHee[editConn]->connectionsList.size(); i++) {
                    if(familyTreeHee[editConn]->connectionsList[i] == temp) {
                      index2 = i;
                    }
                  }
                  temp->connectionsList.erase(temp->connectionsList.begin() + index);
                  temp->connectionsName.erase(temp->connectionsName.begin() + index);
                  familyTreeHee[editConn]->connectionsList.erase(familyTreeHee[editConn]->connectionsList.begin() + index2);
                  familyTreeHee[editConn]->connectionsName.erase(familyTreeHee[editConn]->connectionsName.begin() + index2);
                  cout << "\nConnection deleted.\n";
              } else {
                  break;
              }
            } else {
              cout << "\nConnection not found, please try again";
            }
          }


      } else if (edit == 4) {
          string newDesc = readLine("Please enter new description: ");
          temp->description = newDesc;
          cout << "Description updated to " << ".\n";
        
      } else if (edit == 5) {
        break;
      }
    }
}


void familyTree::deleteFamilyMember() {
  cin.ignore();
  string name;
    while(true) {
      name = readLine("Enter family member's name(Type 'tree' to print family tree): ");
        if(name == "tree") {
          printMapNames();
          continue;
        }
        if(ifFound(name)) {
          break;
        } else {
          continue;
        }
    }
  
  //fix it to where family members also remove this person
  for(int i = 0; i < familyTreeHee[name]->connectionsList.size(); i++) {
    familyMember *& temp =  familyTreeHee[name]->connectionsList[i];
    auto it = find(temp->connectionsList.begin(), temp->connectionsList.end(), familyTreeHee[name]);
    if (it != temp->connectionsList.end()) {
      int index = distance(temp->connectionsList.begin(), it);
      temp->connectionsList.erase(temp->connectionsList.begin() + index);
      temp->connectionsName.erase(temp->connectionsName.begin() + index);
    }
  } 

  familyTreeHee.erase(name);
  cout << "\nFamily member erased.";
}



//----Helping Functions----//

//LINE READER
string familyTree::readLine(string prompt) {
 // cin.ignore();
  string input;
  cout << prompt;
  getline(cin, input);
  return input;
}


//INT READER
int familyTree::readInt(string prompt) {
  int input;
  cout << prompt;
  cin >> input;
  cin.ignore();
  return input;
}


//PRINT FAMILY TREE NAMES
void familyTree::printMapNames() {
  cout << "\n----Family Tree----\n";
  for(map<string, familyMember*>::iterator it = familyTreeHee.begin(); it != familyTreeHee.end(); it++) {
    pair<string, familyMember*> temp = *it;
    cout << temp.first << endl << endl;
  }
  cout << "-------------------\n";
}


//PRINT FAMILY TREE DATA
void familyTree::printFamilyTree() {
  cout << "\n----Family Tree----\n";
  for(map<string, familyMember*>::iterator it = familyTreeHee.begin(); it != familyTreeHee.end(); it++) {
    pair<string, familyMember*> temp = *it;
    printFamilyMember(temp.second);
  }
}


//PRINT SINGULAR FAMILY MEMBER
void familyTree::printFamilyMember(familyMember* temp) {
  cout << "\n--------\n"<< temp->fullName << "\n" << temp->birthYear << "\n" << temp->description << "\nRelations:\n";
  printConnections(temp);
}


//print connections
void familyTree::printConnections(familyMember* temp) {
  for(int i = 0; i < temp->connectionsList.size(); i++) {
    cout << "  " << temp->connectionsName[i] << " to " << temp->connectionsList[i]->fullName << endl;
  }
}



//returns if should run again, adds connection to person
bool familyTree::addConnections(familyMember *& newMember, string prompt, bool isEdit) {  
    
    //prompt for relative name
    string relativeName = readLine(prompt);
    if(relativeName == newMember->fullName) {
      cout << "\nCannot add person as their own relative.\n";
      return true;
    }
        //if tree input
        if(relativeName == "tree") {
          printMapNames();
          return true;
        }

        //if empty
        if(relativeName == "") {

          //if edit, not new
          if(isEdit) {
            return false;
          //if no connections
          } else if (!fRunThrough) {
            cout << "\nMust create at least one connection to the family tree.";
            return true;
          } else {
            return false;
          }

        //if not empty
        } else {
            //if found
            if(ifFound(relativeName)) {
              string relation1;
              string relation2;

              bool newRelation = false;

              //loops through relationship options
              cout << "\n--------\n";
              for(int i = 0; i < relations.size(); i++) {
                cout << i+1 << ") " << relations[i] << endl;
              }

                //gets user input for relation 1
                int relationInputNum = readInt("\nEnter relation of " + newMember->fullName + " to " + relativeName + "(type '0' for custom relation): ");
                  //if want custom input
                  if(relationInputNum == 0) {
                    string custom1 = readLine("Enter custom relation: ");
                    relations.push_back(custom1);
                    newRelation = true;
                  }

                  //checks if new relation was added for relation 1
                  if(newRelation) {
                    relation1 = relations[relations.size()-1];
                  } else {
                    relation1 = relations[relationInputNum-1];
                  }


              newRelation = false;
              //loops through relationship options
              cout << endl;
              for(int i = 0; i < relations.size(); i++) {
                  cout << i+1 << ") " << relations[i] << endl;
                }

                //gets user input for relation 2
                relationInputNum = readInt("\nEnter the relation of " + relativeName + " to " + newMember->fullName + "(type '0' for custom relation): ");
                  //if want custom input
                  if(relationInputNum == 0) {
                    string custom2 = readLine("Enter custom relation: ");\
                    relations.push_back(custom2);
                    newRelation = true;
                  }

                  //checks if new relation was added for relation 2
                  if(newRelation) {
                    relation2 = relations[relations.size()-1];
                  } else {
                      relation2 = relations[relationInputNum-1];
                  }

              //adds to new member and existing family member
              newMember->connectionsList.push_back(familyTreeHee[relativeName]);
              newMember->connectionsName.push_back(relation1);
              familyTreeHee[relativeName]->connectionsList.push_back(newMember);
              familyTreeHee[relativeName]->connectionsName.push_back(relation2);

              //if edit, stop
              if(isEdit) {
                return false;
              } 
              //change prompt
              if(!fRunThrough) {
                fRunThrough = true;
              }

            } 
            return true;
        }
}


bool familyTree::ifFound(string name) {
  if(familyTreeHee.count(name) == 0) {
    cout << "\nFamily Member not found, please try again";
    return false;
  }
  return true;
}