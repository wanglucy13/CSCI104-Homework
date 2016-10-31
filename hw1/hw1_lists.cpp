#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct Item {
	Item(int v, Item* n) {
		val = v;
		next = n;
	}
	int val;
	Item* next;
};

Item* concatenate(Item* head1, Item* head2);
Item* concatenateHelper(Item* head1, Item* head2);
void removeEvens(Item*& head);
double findAverage(Item* head);
double findAverageHelper(Item* head, double sum, double count);
void readLists(Item*& head1, Item*& head2, char*);
//void readLIstsHelper()
void printList(std::ostream& ofile, Item* head);

int main(int argc, char* argv[]) {
	Item* head1 = NULL;
	Item* head2 = NULL;
	Item* head3 = NULL;
	ifstream ifile;
	ifile.open(argv[1]);
	ofstream ofile(argv[2]);

	readLists(head1, head2, argv[1]);
	//printList(ofile, head1);
	//printList(ofile, head2);
	head3 = concatenate(head1, head2);
	printList(ofile, head3);
	removeEvens(head3);
	printList(ofile, head3);
	cout << findAverage(head3) << endl;
	printList(ofile, head3);

}

Item* concatenate(Item* head1, Item* head2) {
	if (head1 == NULL){ 
		return head2;
	}
	else if (head2 == NULL) {
		return head1;
	}
	else if (head1 == NULL && head2 == NULL){
		return NULL;
	}
	else {
		Item* newHead;
		newHead = head1;
		concatenateHelper(newHead, head2);
		return newHead;
	}
}

Item* concatenateHelper(Item* newHead, Item* head2){
	if (newHead -> next == NULL){
		newHead -> next = head2;
	}
	else if (newHead -> next != NULL){
		concatenateHelper(newHead -> next, head2); 
	}
}

void removeEvens(Item*& head) {
	Item* newHead;
	newHead = head;

	if(head == NULL){
		return;
	}

	else if((head -> val) % 2 == 0){
		head = newHead -> next;
		delete newHead;
		removeEvens(head);
		}

	else removeEvens(head -> next);
}

double findAverage(Item* head){ //Find Average function does not work... sorry :(
	double sum = 0.0;
	double count = 0.0;
	double average;
	average = sum/count;
	findAverageHelper(head, sum, count);
	return average;
}

double findAverageHelper(Item* head, double sum, double count) {
	if (head == NULL){
		return 0.0;
	}
	else {
		sum += head -> val;
		findAverageHelper(head -> next, sum, count+1.0);
	}
	return sum;
}

void readLists(Item*& head1, Item*& head2, char* ifile) {
	ifstream filename;
	filename.open(ifile);

	int value1;
	int value2;
	string list1;
	string list2;

	getline(filename, list1);
	getline(filename, list2);
	istringstream iss1(list1);
	istringstream iss2(list2);

	//cout << list2;
	
	iss1 >> value1;
	if (!iss1.fail()) {
		head1 = new Item(value1, NULL);
	}
	Item* curr;
	curr = head1;
	
	iss1 >> value1;
	while(!iss1.fail()) {
		//iss1 >> value1;
		Item* nextVal;
		nextVal = new Item(value1, NULL);
		curr -> next = nextVal;
		curr = curr -> next;
		iss1 >> value1;
	}	

	iss2 >> value2;
	if (!iss2.fail()) {
		head2 = new Item(value2, NULL);
	}
	curr = head2;

	iss2 >> value2;
	while(!iss2.fail()) {
		Item* nextVal;
		nextVal = new Item(value2, NULL);
		curr -> next = nextVal;
		curr = curr -> next;
		iss2 >> value2;
	}
}

void printList(std::ostream& ofile, Item* head) {
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}