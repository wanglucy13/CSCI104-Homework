#include "llistint.h"
#include <iostream>

using namespace std;

int main(){
	LListInt list;

	list.push_back(0);
	if(list.get(0) == 0){
		cout << "SUCCESS: Location 0's value is 0" << endl;
	}
	else{
		cout << "FAIL: Value should be 0 and not " << list.get(0) << endl;
	}

	list.push_back(1);
	if(list.get(1) == 1){
		cout << "SUCCESS: Location 1's value is 1" << endl;
	}
	else{
		cout << "FAIL: Value should be 1 and not " << list.get(1) << endl;
	}
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	if(list.get(4) == 4){
		cout << "SUCCESS: Location 4's value is 4" << endl;
	}
	else{
		cout << "FAIL: Value should be 4 and not " << list.get(4) << endl;
	}

	LListInt list2; //creates new list2
	list2 = list;	//sets list2 to original list

	if(list2.size() == 5){
		cout << "SUCCESS: Size of list is 5" << endl;
	}
	else{
		cout << "FAIL: Size of list is not 5 but is " << list2.size() << endl;
	}

	if(list2.get(1) == 1){
		cout << "SUCCESS: Location 1's value is 1" << endl;
	}
	else{
		cout << "FAIL: Value should be 1 and not " << list.get(1) << endl;
	}

}