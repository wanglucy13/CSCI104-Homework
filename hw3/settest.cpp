#include "setint.h"
#include "llistint.h"
#include <iostream>

using namespace std;

int main(){
	SetInt set;

	// Check if the set is initially empty.
	if (set.empty()) {
	cout << "SUCCESS: set is empty initially." << endl;
	} 
	else {
	cout << "FAIL: set is not empty initially when it should be." << endl;
	}

	// Insert an item at the head.
	set.insert(0);

	// Check if the set is still empty.
	if (!set.empty()) {
	cout << "SUCCESS: set is not empty after one insertion." << endl;
	} 
	else {
	cout << "FAIL: set is empty after one insertion." << endl;
	}

	if (set.size() == 1) { //check if size is one after 1 insert
	cout << "SUCCESS: set has size 1 after one insertion." << endl;
	} 
	else {
	cout << "FAIL: set has size " << set.size() << " after one insertion.";
	cout << endl;
	}

	// Check if the value is correct.
	if (set.exists(0)) {
	cout << "SUCCESS: 0 exists in the set." << endl;
	} 
	else {
	cout << "FAIL: 0 does not exist in the set" << endl;
	}

	set.insert(1);

	if (set.exists(1)){ //check if get function is correct
	cout << "SUCCESS: 1 exists in the set." << endl;
	}
	else{
	cout << "FAIL: 1 does not exist in the set" << endl;
	}

	if(set.size() == 2){ //check if size is correct after 2 inserts
	cout << "SUCCESS: The set has size 2 after 2 insertions" << endl;
	}
	else{
	cout << "FAIL: set has size " << set.size() << " after 2 insertions";
	cout << endl; 
	}

	set.remove(1);
	if(set.size() == 1){ 
	cout << "SUCCESS: Size of set is 1 after removal" << endl;
	}
	else{
	cout << "FAIL: Size of set is not 1 and is " << set.size() << endl;
	}

	if (!set.exists(1)) {
	cout << "SUCCESS: 1 does not exist after removal." << endl;
	} 
	else {
	cout << "FAIL: 1 is still in the set" << endl;
	}

	set.remove(100);

	if(set.size() == 1){ 
	cout << "SUCCESS: Size of set is still 1 after incorrect removal" << endl;
	}
	else{
	cout << "FAIL: Size of set is not 1 and is " << set.size() << endl;
	}

	for(int i = 1; i < 7; i++){
		set.insert(i);
	}

	if(*(set.first()) == 0){
		cout << "SUCCESS: First element is 0" << endl;
	}
	else{
		cout << "FAIL: First element is not 0 but" << set.first() << endl;
	}

	if(*(set.first()) == 0){
		cout << "SUCCESS: First element is 0" << endl;
	}
	else{
		cout << "FAIL: First element is not 0 but" << *(set.first()) << endl;
	}

	if(*(set.next()) == 1){
		cout << "SUCCESS: Next element is 1" << endl;
	}
	else{
		cout << "FAIL: Next element is not 1 but" << *(set.next()) << endl;
	}

	if(*(set.next()) == 2){
		cout << "SUCCESS: Next element is 2" << endl;
	}
	else{
		cout << "FAIL: Next element is not 2 but" << *(set.next()) << endl;
	}

	SetInt set2, set3, set4;

	for(int i = 4; i < 8; i++){
		set2.insert(i);
	}

	set3 = set2&set;
	cout << "SUCCESS: union of both sets is "; 
	cout << *(set3.first());
	for(int i = 1; i < set3.size(); i++){
		cout << ", " << *(set3.next());
	}
	cout << endl;

	set4 = set2|set;
	cout << "SUCCESS: intersection of both sets is "; 
	cout << *(set4.first());
	for(int i = 1; i < set4.size(); i++){
		cout << ", " << *(set4.next());
	}
	cout << endl;

}

