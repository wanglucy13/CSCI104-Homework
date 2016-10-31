#include "llistint.h"
#include "setint.h"
#include <iostream>

using namespace std;

/**
 * Default constructor - default to a list of capacity = 10
 */
SetInt::SetInt(){
  list_ = LListInt();
}

/**
 * Destructor
 */
SetInt::~SetInt(){
  
}

/**
 * Returns the current number of items in the list 
 */
int SetInt::size() const{
  return list_.size();
}

/**
 * Returns true if the list is empty, false otherwise
 */
bool SetInt::empty() const{
  if(list_.size() == 0){
    return true;
  }
  else{
    return false;
  }
}

/**
 * Inserts val so it appears at index, pos
 */
void SetInt::insert(const int& val){
  if(!exists(val)){
    list_.push_back(val);
  }
  else{
    return;
  }
}

/**
 * Removes the value at index, pos
 */
void SetInt::remove(const int& val){
  if(exists(val)){
    list_.remove(val);
  }
  else{
    return;
  }
}

/**
 * Returns true if the item is in the set
 */
bool SetInt::exists(const int& val) const{
  for(int i = 0; i < size(); i++){
    if(list_.get(i) == val){
      return true;
    }
  }
  return false;
}

/**
 * Return a pointer to the first item
 *  and support future calls to next()
 */
int const* SetInt::first(){
  current = 0;
  if(!list_.empty()){
    return &(list_.get(current));
  }
  else{
    return NULL;
  }
}

/**
 * Return a pointer to the next item
 *  after the previous call to next
 *  and NULL if you reach the end
 */
int const* SetInt::next(){
  if(current != list_.size()){
    current++; 
    return &(list_.get(current));
  }
  return NULL;
}

/**
 * Returns another (new) set that contains
 * the union of this set and "other"
 */
SetInt SetInt::setUnion(const SetInt& other) const{ 
  SetInt UnionSet;
  for(int i = 0; i < other.size(); i++){
    if(!exists(other.list_.get(i))){
      UnionSet.list_.push_back(other.list_.get(i));
    }
  }
  for(int i = 0; i < list_.size(); i++){
    if(!other.exists(list_.get(i))){
      UnionSet.list_.push_back(list_.get(i));
    }
  }
  return UnionSet;
}

/**
 * Returns another (new) set that contains
 * the intersection of this set and "other"
 */
SetInt SetInt::setIntersection(const SetInt& other) const{
  SetInt InterSet;
  for(int i = 0; i < list_.size(); i++){
    for(int j = 0; j < other.size(); j++){
      if(list_.get(i) == other.list_.get(j)){
        InterSet.list_.push_back(list_.get(i));
      }
    }
  } 
  return InterSet;
}

SetInt SetInt::operator|(const SetInt& other) const{ 
  SetInt UnionSet;
  for(int i = 0; i < other.size(); i++){
    if(!exists(other.list_.get(i))){
      UnionSet.list_.push_back(other.list_.get(i));
    }
  }
  for(int i = 0; i < list_.size(); i++){
    if(!other.exists(list_.get(i))){
      UnionSet.list_.push_back(list_.get(i));
    }
  }
  return UnionSet;
}

SetInt SetInt::operator&(const SetInt& other) const{
  SetInt InterSet;
  for(int i = 0; i < list_.size(); i++){
    for(int j = 0; j < other.size(); j++){
      if(list_.get(i) == other.list_.get(j)){
        InterSet.list_.push_back(list_.get(i));
      }
    }
  } 
  return InterSet;
}
