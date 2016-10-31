#include "alistint.h"
#include <iostream>

using namespace std;

int main() {
  //int capacity = maxcap;
  AListInt* list = new AListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } 
  else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }
  // Insert an item at the head.  
  list->insert(0, 1);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } 
  else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } 
  else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 1) {
    cout << "SUCCESS: 1 is at the 0th index of the list." << endl;
  } 
  else {  
    cout << "FAIL: 1 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list -> insert(1, 2);
  list -> insert(2, 3);
  list -> insert(3, 4);
  list -> insert(4, 5);
  list -> insert(5, 6);


  if (!list->empty()) { //check if list is not empty after insertion
      cout << "SUCCESS: List is not empty after 6 insertions." << endl;
    } 
  else {
      cout << "FAIL: List is empty after 6 insertions." << endl;
    }

  if (list->size() == 6) { //check if size is correct
    cout << "SUCCESS: List has size 6 after 6 insertions." << endl;
  } 
  else {
    cout << "FAIL: List has size " << list->size() << " after 6 insertions.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(4) == 5) { 
    cout << "SUCCESS: 5 is at the 4th index of the list." << endl;
  } 
  else {  
    cout << "FAIL: 5 is not at the 4th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  list -> remove(4);
  list -> remove(0);
  list -> remove(2);

  if (list->size() == 3) { //check if size is correct after removals
    cout << "SUCCESS: List has size 3 after removing 3 items." << endl;
  } 
  else {
    cout << "FAIL: List has size " << list->size();
    cout << " after removing 3 items." << endl;
  }

  // Check if the value is correct after removal
  if (list->get(1) == 2) {
    cout << "SUCCESS: 2 is at the 1st index of the list." << endl;
  } 
  else {  
    cout << "FAIL: 2 is not at the 1st index of the list, " << list->get(1);
    cout << " is instead." << endl;
  }

  list -> insert(3, 4);
  list -> insert(4, 5);
  list -> insert(5, 6);
  list -> insert(6, 4);
  list -> insert(7, 5);
  list -> insert(8, 6);
  list -> insert(9, 4);
  list -> insert(10, 5);
  list -> insert(11, 6);

  if (list->size() == 12) { //check is size is correct after insertion
    cout << "SUCCESS: List has size 12 after inserting 12 items." << endl;
  } 
  else {
    cout << "FAIL: List has size " << list->size();
    cout << " after inserting 11 items." << endl;
  }

  // Check if the value is correct.
  if (list->get(10) == 5) {
    cout << "SUCCESS: 5 is at the 10th index of the list." << endl;
  } 
  else {  
    cout << "FAIL: 5 is not at the 10th index of the list, " << list->get(1);
    cout << " is instead." << endl;
  }

  list -> set(3, 123);
  if (list -> get(3) == 123){ //check is set function works
    cout << "SUCCESS: Set function sets 3rd index to 123!" << endl;
  }
  else{
    cout <<"FAIL: Set function does not set 3rd index to 123.";
    cout << "Instead sets it to" << list -> get(3) << endl;
  }

  // Clean up memory.
  delete list;
}