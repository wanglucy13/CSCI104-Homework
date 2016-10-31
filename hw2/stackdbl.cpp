#include "stackdbl.h"
#include "llistdbl.h"
#include <iostream>
using namespace std;

 StackDbl::StackDbl(){
 	list_ = LListDbl(); 
 }

 StackDbl::~StackDbl(){
 	list_.clear();
 }

/**
* Returns true if the stack is empty, false otherwise
*/
bool StackDbl::empty() const{
	if(list_.empty()){
		return true;
	}
	else
		return false;
}

/**
* Pushes a new value, val, onto the top of the stack
*/
void StackDbl::push(const double& val){
	list_.insert(list_.size(), val);
}

/**
* Returns the top value on the stack
*/
double const & StackDbl::top() const{
	list_.get(list_.size()-1);
}

/**
* Removes the top element on the stack
*/
void StackDbl::pop(){
	list_.remove(list_.size()-1);
}
