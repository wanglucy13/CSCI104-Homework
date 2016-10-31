#ifndef HEAP_H
#define HEAP_H
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <iostream>

using namespace std;

template <typename T, typename Comparator >
class Heap
{
 public:
  Heap(int m, Comparator c);
  ~Heap();
  void push(const T& item);
  T const & top() const;
  void pop();
  bool empty() const;
  int size();

 private:
  /// Add whatever helper functions and data members you need below
 	Comparator comp;
 	int m_;
 	vector<T> heap;
 	void trickleDown(int pos);
 	void trickleUp(int pos);
};

// Add implementation of member functions here


template <typename T, typename Comparator >
/// Constructs an m-ary heap for any m >= 2
Heap<T, Comparator>::Heap(int m, Comparator c){
	m_ = m;
	comp = c;
}

template <typename T, typename Comparator >
Heap<T,Comparator>::~Heap(){

}

template <typename T, typename Comparator >
int Heap<T,Comparator>::size() {
	return heap.size();
}

/// Adds an item
template <typename T, typename Comparator >
void Heap<T,Comparator>::push(const T& item){
	heap.push_back(item);
	trickleUp(heap.size() - 1);
}

template <typename T, typename Comparator >
void Heap<T,Comparator>::trickleUp(int pos){
	int parent = (pos - 1)/m_;
	if(pos > 0 && comp(heap[pos], heap[parent])){
		T temp = heap[parent];
		heap[parent] = heap[pos];
		heap[pos] = temp;

		trickleUp((pos-1)/m_);
	}
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  if(empty()){
    throw std::logic_error("Can't top an empty heap");
  }
  else{
  	return heap[0];
  }
}

// We will start pop() for you to handle the case of 
// calling pop on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
	if(empty()){
		throw std::logic_error("Can't pop an empty heap");
	}
	else{
		heap[0] = heap[heap.size() - 1];
		heap.pop_back();
		trickleDown(0);
	}
}

template <typename T, typename Comparator >
void Heap<T,Comparator>::trickleDown(int pos){
	if(heap.size() <= 1){
		return;
	}

	if(pos * m_ > heap.size() - 1 ){
		return;
	}

	else{
		int smallestChild = pos * m_ + 1;
		if(smallestChild + m_ < heap.size()){
			for(int i = smallestChild; i < smallestChild + m_; i++){
				if(comp(heap[i], heap[smallestChild])){
					smallestChild = i;
				}
			}
		}

		else if(smallestChild * m_ + 1 < heap.size()){
			for(int i = smallestChild; i < smallestChild + m_; i++){
				if(comp(heap[i], heap[smallestChild])){
					smallestChild = i;
				}
			}
		}

		else{
			for(int i = smallestChild; i < heap.size(); i++){
				if(comp(heap[i], heap[smallestChild])){
					smallestChild = i;
				}
			}
		}

		if(!comp(heap[pos], heap[smallestChild])){
			T temp = heap[smallestChild];
			heap[smallestChild] = heap[pos];
			heap[pos] = temp;
			trickleDown(smallestChild);
		}
	}
}

/// returns true if the heap is empty
template <typename T, typename Comparator >
bool Heap<T,Comparator>::empty() const{
	if(heap.size() == 0){
		return true;
	}
	else return false;
}

#endif

