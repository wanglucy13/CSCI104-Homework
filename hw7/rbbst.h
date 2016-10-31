/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"
/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }


  RedBlackNode<KeyType, ValueType> *getGrandparent(){
    if(this -> getParent() != NULL && this -> getParent() -> getParent() != NULL){
      return this -> getParent() -> getParent();
    }
    return NULL;
  }


  RedBlackNode<KeyType, ValueType> *getUncle(){
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
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert (const std::pair<const KeyType, ValueType>& new_item){
	//if new_item is not in the tree 
	if(this -> find(new_item.first) == this -> end()){
		RedBlackNode<KeyType, ValueType>* p = (RedBlackNode<KeyType, ValueType>*) this -> root;
		// this -> printRoot(n);

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
		RedBlackNode<KeyType, ValueType>* n = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, p);

		if(this -> root == NULL){
			this -> root = n;
			fixTree(n);
		} 
		else{
			if(new_item.first < p -> getKey()){
				p -> setLeft(n);

			}
			else{
				p -> setRight(n);
			}
			fixTree(n);
		}
	}
	// else if new_item is in the tree overwrite 
	else if(this -> find(new_item.first) != this -> end()){ 
		(*(this -> find(new_item.first))).second = new_item.second;
	}
   }

private:
  bool rightChild(RedBlackNode<KeyType, ValueType>* n){
  	if(n -> getParent() == NULL){
  		return false;
  	}
	else if(n == n -> getParent() -> getRight()){
		return true;
	}
	else return false;
  }

  bool leftChild(RedBlackNode<KeyType, ValueType>* n){
  	if(n -> getParent() == NULL){
  		return false;
  	}
	else if(n == n -> getParent() -> getLeft()){
		return true;
	}
	else return false;
  }

  void fixTree(RedBlackNode<KeyType, ValueType> *n){
  	//if n is root set color to black
  	if(n -> getParent() == NULL){
  		n -> setColor(black);
  	}
  	else if(n -> getParent() ->getColor() == black){
  		return;
  	}
  	else if(n -> getUncle() != NULL && n -> getUncle() -> getColor() == red){
  		n -> getParent() -> setColor(black);
		n -> getUncle() -> setColor(black);
		n -> getGrandparent() -> setColor(red);
		fixTree(n -> getGrandparent());
  	}
  	else if(rightChild(n) && leftChild(n -> getParent())){
  		RedBlackNode<KeyType, ValueType> *grandparent = n -> getGrandparent();
	  	RedBlackNode<KeyType, ValueType> *parent = grandparent -> getLeft();
  	  	RedBlackNode<KeyType, ValueType> *left = n -> getLeft();
  	  	grandparent -> setLeft(n);
  	  	n -> setLeft(parent);
  	  	parent -> setRight(left);
  	  	rotateRight(grandparent);
  	}
  	else if(leftChild(n) && (rightChild(n -> getParent()))){
  	  	RedBlackNode<KeyType, ValueType> *grandparent = n -> getGrandparent();
	  	RedBlackNode<KeyType, ValueType> *parent = grandparent -> getRight();
  	  	RedBlackNode<KeyType, ValueType> *right = n -> getRight();
  	  	grandparent -> setRight(n);
  	  	n -> setParent(grandparent);
  	  	n -> setRight(parent);
  	  	parent -> setParent(n);
  	  	parent -> setLeft(right);
  	  	// fixTree(grandparent);
  	  	rotateLeft(grandparent);
  	}

  	else{
  		n -> getParent() -> setColor(black);
  		n -> getGrandparent() -> setColor(red);
  		if(leftChild(n)){
 			rotateRight(n -> getGrandparent());
  		}
  		else{
			rotateLeft(n -> getGrandparent());		  
	  	  }
  	}
  }

  void rotateLeft(RedBlackNode<KeyType, ValueType> *n){
  	RedBlackNode<KeyType, ValueType> *temp = n -> getRight();
    n -> setRight(temp -> getLeft());
    if (temp -> getLeft() != NULL ){
        temp -> getLeft() -> setParent(n);
        temp -> setParent(n);
    }
    temp -> setParent(n -> getParent());
    if(n -> getParent() == NULL ){ 
    	this ->root = temp;
    }
    else
        if (leftChild(n))
            n -> getParent()-> setLeft(temp);
        else
            n -> getParent() -> setRight(temp);
    temp -> setLeft(n);
    n -> setParent(temp);
	}

  void rotateRight(RedBlackNode<KeyType, ValueType> *n){
  	RedBlackNode<KeyType, ValueType> *temp = n -> getLeft();
    n -> setLeft(temp -> getRight());
    if (temp -> getRight() != NULL ){
        temp -> getRight() -> setParent(n);
        temp -> setParent(n);
    }
    temp -> setParent(n -> getParent());
    if(n -> getParent() == NULL ){ 
    	this ->root = temp;
    }
    else
        if (rightChild(n))
            n -> getParent()-> setLeft(temp);
        else
            n -> getParent() -> setRight(temp);
    n -> setLeft(temp);
    temp -> setParent(n);
  }

};

