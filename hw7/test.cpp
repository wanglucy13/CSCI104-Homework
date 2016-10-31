#include "rbbst.h"
#include <iostream>
#include <utility>

using namespace std;

int main(){

	RedBlackTree<int, string>* tree = new RedBlackTree<int,string>();

	pair<int, string> p1(10, "a");
	tree->insert(p1);
	cout << "Insert (10, a)" << endl;
	tree -> print();

	pair<int, string> p2(20, "b");
	tree->insert(p2);
	cout << "Insert (20, b)" << endl;
	tree -> print();

	pair<int, string> p3(30,"c");
	tree->insert(p3);
	cout << "Insert (30, c)" << endl;
	tree -> print();

	pair<int, string> p4(15,"d");
	tree->insert(p4);
	cout << "Insert (15, d)" << endl;
	tree -> print();

	pair<int, string> p5(25,"e");
	tree->insert(p5);
	cout << "Insert (25, e)" << endl;
	tree -> print();

	pair<int, string> p6(12,"f");
	tree->insert(p6);
	cout << "Insert (12, f)" << endl;
	tree -> print();

	pair<int, string> p7(5,"g");
	tree->insert(p7);
	cout << "Insert (5, g)" << endl;
	tree -> print();

	pair<int, string> p8(3,"h");
	tree->insert(p8);
	cout << "Insert (3, h)" << endl;
	tree -> print();


	pair<int, string> p9(8,"i");
	tree->insert(p9);
	cout << "Insert (8, i)" << endl;
	tree -> print();

	return 0;
}