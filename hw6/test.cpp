#include "heap.h"
#include <iostream>
#include <functional>

using namespace std;

int main(){
	less<int> l;
	greater<int> g;

	Heap<int, less<int> > a(2, l);
	Heap<int, greater<int> > b(2, g);

	b.push(3);
	b.push(22);
	b.push(6);
	b.push(8);
	b.push(1);
	b.push(4);

	cout <<	b.top() << endl;
	b.pop();

	cout << b.top() << endl;
	b.pop();

	cout << b.top() << endl;
	b.pop();

	cout << b.top() << endl;
	b.pop();

	cout << b.top() << endl;
	b.pop();

	cout << b.top() << endl;
}
