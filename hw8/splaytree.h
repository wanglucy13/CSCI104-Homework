#include "bst.h"
#include <iostream>
#include <exception>
#include <cstdlib>

template <class KeyType, class ValueType>
class SplayNode : public Node<KeyType, ValueType>
{
public:
  SplayNode (KeyType k, ValueType v, SplayNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { }
  
  virtual ~SplayNode () {}

  SplayNode<KeyType, ValueType> *getGrandparent(){
    if(this -> getParent() != NULL && this -> getParent() -> getParent() != NULL){
      return this -> getParent() -> getParent();
    }
    return NULL;
  }


  SplayNode<KeyType, ValueType> *getUncle(){
	if(this -> getParent() != NULL && this -> getGrandparent() != NULL){
		if(this -> getParent() == this -> getGrandparent() -> getLeft()){
	    	return this -> getGrandparent() -> getRight();
     	}
     	else if(this -> getParent() == this -> getGrandparent() -> getRight()){
	    	return this -> getGrandparent() -> getLeft();
		}
    }
    return NULL;
  }
  
  virtual SplayNode<KeyType, ValueType> *getParent () const
    { return (SplayNode<KeyType,ValueType>*) this->_parent; }
  
  virtual SplayNode<KeyType, ValueType> *getLeft () const
    { return (SplayNode<KeyType,ValueType>*) this->_left; }
  
  virtual SplayNode<KeyType, ValueType> *getRight () const
    { return (SplayNode<KeyType,ValueType>*) this->_right; }

};

template <class KeyType, class ValueType>
class SplayTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert(const std::pair<const KeyType, ValueType>& new_item){
    SplayNode<KeyType, ValueType>* p = (SplayNode<KeyType, ValueType>*) this -> root;
    while(p != NULL){
      if(new_item.first < p -> getKey()){
        if(p -> getLeft() != NULL){
          p = p -> getLeft();
        }
        else if(p -> getLeft() == NULL){
          break;
        }
      }
      else{
        if(p -> getRight() != NULL){
          p = p -> getRight();
        }
        else if(p -> getRight() == NULL){
          break;
        }
      }
    }
    SplayNode<KeyType, ValueType>* n = new SplayNode<KeyType, ValueType>(new_item.first, new_item.second, p);

    if(this -> root == NULL){
      this -> root = n;
    } 
    else{
      if(new_item.first < p -> getKey()){
        p -> setLeft(n);

      }
      else{
        p -> setRight(n);
      }
      SplayTree(n);
    }
  }

  SplayNode<KeyType, ValueType>* find(const KeyType &k){
    SplayNode<KeyType, ValueType> *n = internalFind(k);
    if(n != NULL){
      splayTree(n);
    }
    else
      return n;
   }

   SplayNode<KeyType, ValueType>* internalFind(const KeyType& k) const 
  {
    SplayNode<KeyType, ValueType> *curr =(SplayNode<KeyType, ValueType>* ) this -> root;
    while (curr) {
      if (curr->getKey() == k) {
  return curr;
      } else if (k < curr->getKey()) {
  curr = curr->getLeft();
      } else {
  curr = curr->getRight();
      }
    }
    return NULL;
  }

private:
  

  bool rightChild(SplayNode<KeyType, ValueType>* n){
  	if(n -> getParent() == NULL){
  		return false;
  	}
	else if(n == n -> getParent() -> getRight()){
		return true;
	}
	else return false;
  }

  bool leftChild(SplayNode<KeyType, ValueType>* n){
  	if(n -> getParent() == NULL){
  		return false;
  	}
	else if(n == n -> getParent() -> getLeft()){
		return true;
	}
	else return false;
  }

  void splayTree(SplayNode<KeyType, ValueType> *n) {
       // Base cases: root is NULL or key is present at root
    while(this -> root != n){
      if((SplayNode<KeyType, ValueType>* ) this -> root == n){
         std::cout << "roooooot" << std::endl;
          return;
      }
      //if n's parent is the root
      else if(n -> getParent() == (SplayNode<KeyType, ValueType>* ) this -> root){
      	if((SplayNode<KeyType, ValueType>* ) this -> root -> getLeft() == n){
          std::cout << "root right rotate" << std::endl;
      		rotateRight(n);
      	} 
      	else{
          std::cout << "root left rotate" << std::endl;

      		rotateLeft(n);
      	}
      }
      else{
        //left left
  	   	if(leftChild(n) && leftChild(n -> getParent())){
          std::cout << "left left rotate" << std::endl;
          rotateRight(n->getParent());
          rotateRight(n);
          // n -> getRight() -> setRight(n -> getParent());
          // n -> setParent(n -> getGrandparent());       
  	    }
        //right right
  		  else if(rightChild(n) && rightChild(n -> getParent())){
          std::cout << "right right rotate" << std::endl;
          rotateLeft(n->getParent());
          rotateLeft(n);
  	    	// n -> getLeft() -> setLeft(n -> getParent());
        //   n -> setParent(n -> getGrandparent());
  	    }
        //right left
  	    else if(rightChild(n) && leftChild(n -> getParent())){
          std::cout << "right left rotate" << std::endl;
          SplayNode<KeyType, ValueType> *grandparent = n -> getGrandparent();
          SplayNode<KeyType, ValueType> *parent = grandparent -> getLeft();
          SplayNode<KeyType, ValueType> *left = n -> getLeft();
  	    	grandparent -> setLeft(n);
          n -> setLeft(parent);
          parent -> setRight(left);
  	    	rotateRight(n -> getParent());
  	    }
        //left right
  	    else if(leftChild(n) && rightChild(n -> getParent())){
          std::cout << "left right rotate" << std::endl;
          SplayNode<KeyType, ValueType> *grandparent = n -> getGrandparent();
          SplayNode<KeyType, ValueType> *parent = grandparent -> getRight();
          SplayNode<KeyType, ValueType> *right = n -> getRight();
  	    	grandparent -> setRight(n);
          n -> setParent(grandparent);
          n -> setRight(parent);
          parent -> setParent(n);
          parent -> setLeft(right);
  	    	rotateLeft(n -> getParent());
  	    }
      }
  	}

}
  void rotateLeft(SplayNode<KeyType, ValueType> *n){
    SplayNode<KeyType, ValueType> *temp = n -> getParent();
    temp -> setRight(n -> getLeft());
    if (temp -> getLeft() != NULL ){
        temp -> getLeft() -> setParent(temp);
    }
    n -> setParent(temp -> getParent());
    n -> setLeft(temp);
    if(n -> getParent() == NULL ){ 
      this -> root = n;
    }
    else
        if (rightChild(temp))
            temp -> getParent()-> setRight(n);
        else
            temp -> getParent() -> setLeft(n);
    //n -> setLeft(temp);
    temp -> setParent(n);
	}

  void rotateRight(SplayNode<KeyType, ValueType> *n){
    SplayNode<KeyType, ValueType> *temp = n -> getParent();
    temp -> setLeft(n -> getRight());
    if (temp -> getRight() != NULL ){
        temp -> getRight() -> setParent(temp);
    }
    n -> setParent(temp -> getParent());
    n -> setRight(temp);
    if(n -> getParent() == NULL ){ 
    	this -> root = n;
    }
    else
        if (rightChild(temp))
            temp -> getParent()-> setRight(n);
        else
            temp -> getParent() -> setLeft(n);
    //n -> setRight(temp);
    temp -> setParent(n);
  }
};

