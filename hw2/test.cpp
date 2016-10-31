#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() {
  LListDbl * list = new LListDbl();

  // Check if the list is initially empty.
  if (list -> empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } 
  else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Insert an item at the head.
  list -> insert(0, 3.3);

  // Check if the list is still empty.
  if (!list -> empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } 
  else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list -> size() == 1) { //check if size is one after 1 insert
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } 
  else {
    cout << "FAIL: List has size " << list -> size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list -> get(0) == 3.3) {
    cout << "SUCCESS: 3.3 is at the 0th index of the list." << endl;
  } 
  else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Insert something at the end of the list
  list -> insert(1, 5.1);

  if (list -> get(1) == 5.1){ //check if get function is correct
    cout << "SUCCESS: 5.1 is the last value in the list." << endl;
  }
  else{
    cout << "FAIL: 5.1 is not the last value in the list";
    cout << list -> get(1) << " is instead." << endl;
  }

  if(list -> size() == 2){ //check if size is correct after 2 inserts
    cout << "SUCCESS: The list has size 2 after 2 insertions" << endl;
  }
  else{
    cout << "FAIL: List has size " << list -> size() << " after 2 insertions";
    cout << endl; 
  }

  // Insert something out of bounds
  list -> insert(-1, 4.5);
  if(list -> size() == 2){ //check if out of bounds inserts correctly work
    cout << "SUCCESS: Item did not insert into list" << endl;
  }
  else{
    cout << "FAIL: Item inserted into list when list should be ";
    cout << list -> size() << endl;
  }

  list -> insert(1, 2.8);
  if(list -> get(1) == 2.8){ //check if insert works for insertion in middle
    cout << "SUCCESS: 2.8 is the value at the 1st index of the list." << endl;
  } 
  else{
    cout << "FAIL: 2.8 is not the value at the 1st index, " << list -> get(1);
    cout << " is instead" << endl;
  }

  if(list -> size() == 3){ //check size if size is correct after insertion
    cout << "SUCCESS: The list has size 3 after 3 insertions" << endl;
  }
  else{
    cout << "FAIL: List has size" << list -> size() << " after 3 insertions.";
    cout << endl;
  }

  list -> remove(-1);
  if(list -> size() == 3){ //check if remove works for out of bounds
    cout << "SUCCESS: Size of list is 3 since loc is out of bounds" << endl;
  }
  else{
    cout << "FAIL: Size of list is not 3 and is " << list -> size() << endl;
  }
 
  // cout << list -> size() << endl;
  list -> remove(0);
  // cout << list -> size() << endl;

  if(list -> get(0) != 3.3){ //check if check works after remove
    cout << "SUCCESS: Item removed correctly" << endl;
  }
  else{
    cout << "FAIL: Item did not remove correctly. Value of 0th index ";
    cout << "should not be 3.3." << endl;
  }

  if(list -> size() == 2){ //check if size is correct
    cout << "SUCCESS: Size of list is 2 after 1 removal" << endl;
  }
  else{
    cout << "FAIL: Size of list did not decrease to 2 instead to ";
    cout << list -> size() << endl;
  }

  list -> insert(2, 3.3);
  list -> insert(3, 4.6);
  list -> insert(4, 9.2);
  list -> insert(5, 1.5);  
  list -> insert(6, 7.4);

  list -> remove(1);  
  list -> remove(0);

  if(list -> get(1) != 2.8){ //check if item removed correctly
    cout << "SUCCESS: Item removed correctly" << endl;
  }
  else{
    cout << "FAIL: Item did not remove correctly. Value of 1st index ";
    cout << "should not be 4.6." << endl;
  }

  if(list -> size() == 5){ //check if adding over capacity works
    cout << "SUCCESS: Size of list is 5 after 2 removals" << endl;
  }
  else{
    cout << "FAIL: Size of list did not decrease to 5 instead to ";
    cout << list -> size() << endl;
  }

  list -> clear();
  if(list -> size() == 0){ //checks if clear function works
    cout << "SUCCESS: List cleared successfully" << endl;
  }
  else{
    cout << "FAIL: List did not clear sucessfully. There are still ";
    cout << list -> size() << " items in the list" << endl;
  }

  // Clean up memory.
  delete list;
}