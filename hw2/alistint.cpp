#include "alistint.h"
#include <iostream>

using namespace std;

AListInt::AListInt(){
	size_ = 0;
	maxcap = 10;
	alist = new int[10];

}

AListInt::AListInt(int cap){
	maxcap = cap;
	alist = new int[maxcap];
}

/**
* Destructor
*/
AListInt::~AListInt(){
	delete [] alist;
}

/**
* Standard List interface
*/

/**
* Returns the current number of items in the list 
*/
int AListInt::size() const{
	return size_;
}

/**
* Returns true if the list is empty, false otherwise
*/
bool AListInt::empty() const{
	if(size_ == 0){
		return true;
	}
	else {
		return false;
	}
}

/**
* Inserts val so it appears at index, pos
*/
void AListInt::insert (int pos, const int& val){
	if(pos < 0 || pos > size_){
		return;
	}

	if(size_ == maxcap){
		resize();
	}

	if(pos == size_ && pos != 0 && pos != size_){
		alist[pos] = val; //set alist[pos] to the value and increment size
		size_++;
	}

	else{
		for(int i = size_ ; i > pos; i--){
			alist[i + 1] = alist[i]; 
		}
		alist[pos] = val;
		size_++;
	}
}

/**
* Removes the value at index, pos
*/
void AListInt::remove (int pos){
	if(pos < 0 || pos > size_ - 1){
		return;
	}
	if (pos == size_){
		size_--;
	}
	else{
		for(int i = pos; i > size_ - 1; i++){
			alist[i] = alist[i + 1];
		}
		size_--;
	}
}

/**
* Overwrites the old value at index, pos, with val
*/
void AListInt::set (int position, const int& val){
	alist[position] = val;
}

/**
* Returns the value at index, pos
*/
int& AListInt::get (int position){
	return alist[position];
}

/**
* Returns the value at index, pos
*/
int const & AListInt::get (int position) const{
	return alist[position];
}

void AListInt::resize(){
	int* alist2 = new int[size_ * 2];
	for (int i = 0; i < size_; i++){
		alist2[i] = alist[i];
	}
	maxcap = maxcap * 2;
	delete [] alist;
	alist = alist2;

}
