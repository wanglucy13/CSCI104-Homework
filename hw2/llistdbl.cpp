#include "llistdbl.h"
#include <cstdlib>
#include <iostream>
using namespace std;

LListDbl::LListDbl()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListDbl::~LListDbl()
{
  clear();
}

bool LListDbl::empty() const
{
  return size_ == 0;
}

int LListDbl::size() const
{
  return size_;
}

void LListDbl::insert(int loc, const double& val)
{
	if(loc > size_ || loc < 0){
		return;
	}

   if(size_ == 0){
      Item* newVal = new Item;
      newVal -> next = NULL;
      newVal -> prev = NULL;
      newVal -> val = val;
      head_ = newVal;
      tail_ = newVal;
      size_++;
   }

	else if(loc == 0){
      Item* newVal = new Item;
      Item* oldHead = getNodeAt(0);
      newVal -> val = val;
      newVal -> prev = NULL;
      newVal -> next = oldHead;
      oldHead -> prev = newVal;
      head_ = newVal;
      size_++;
   }

   else if(loc == size_){
   	  Item* oldTail = getNodeAt(loc - 1);
      Item* newVal = new Item;
      newVal -> val = val;
      newVal -> next = NULL;
      newVal -> prev = oldTail;
      oldTail -> next = newVal;
      tail_ = newVal;
      size_++;
   }

   else{
      Item* newVal = new Item;
      newVal -> val = val;
      Item* prevVal = getNodeAt(loc - 1);
      newVal -> prev = prevVal;
      Item* nextVal = getNodeAt(loc);
      newVal -> next = nextVal;
      prevVal -> next = newVal;
      nextVal -> prev = newVal;
      size_++;
   }
}

void LListDbl::remove(int loc)
{
	if(loc > (size_ - 1) || loc < 0 || empty()){
		return;
	}

	if(size() == 1 && loc == 0){
		delete getNodeAt(loc);
    size_--;
	}

	else if(loc == size_ - 1){
    Item* newTail = getNodeAt(loc - 1);
		newTail -> next = NULL;
		delete getNodeAt(loc);
    tail_ = newTail;
		size_--;
   }
   
  else if(loc == 0){
    Item* newHead = getNodeAt(loc + 1);
 		newHead -> prev = NULL;
    delete getNodeAt(loc);
 		head_ = newHead;
 		size_--;
 	}

  else if(loc != 0 && size_ != 0){
 		Item* nextNode = getNodeAt(loc + 1);
 		Item* prevNode = getNodeAt(loc - 1);
    prevNode -> next = nextNode;
    nextNode -> prev = prevNode;
 		delete getNodeAt(loc);
 		size_--;
 }
}

void LListDbl::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

double& LListDbl::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

double const & LListDbl::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListDbl::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListDbl::Item* LListDbl::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
