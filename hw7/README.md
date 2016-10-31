# CS 104 Student Repository

- **Name**: Yi Wang
- **USC ID**: 1114413388
- **Email**: wang796@usc.edu

The makefile is included for the comilation of rectangle and rbbst
All files can be compiled by typing `make` or `make all`
To run rbbst (red black tree program) type `./test` or make your own test file to test
To run rectangle, type `./rectangle input.txt output.txt`

`bst.h` successfully implements a binary search tree. 
It contains a `print()` function which prints the entire tree structure using brackets
The iterator class implements an in-order iterator that allows the user to go through the tree.
The `begin()` function returns an iterator to the smallest item in the tree and returns an iterator. Similarly, `end()` returns a NULL iterator.
The `find()` function takes in a KeyType parameter and returns an  iterator to the item with the given key, k or the end iterator if k does not exist in the tree.

`rbbst.h` uses `bst.h` to implement a red-black tree's insert function by testing all the cases for inserting such as zig zag and recoloring.
`fixTree()` goes through all the cases and fixes the tree accordingly by using `rotateLeft(RedBlackNode<KeyType, ValueType> *n)` and `rotateRight(RedBlackNode<KeyType, ValueType> *n)`
This program did not work for all cases, but worked for most cases. I believe the problem lies within the rightRotate() function.

`rectangle.cpp` tiles a rectangular surface by using rectangles of various shapes and sizes. The input format of the input file is:
						N M X 
						ID1 l1 h1
						ID2 l2 h2
						...
						IDX lX hX
Where N is the length of the surface, M is the height of the surface, X is the number of tiles you have to place, IDi is the identifying number of the ith tile, li is the length of the ith tile, and hi is the height of the ith tile. 
This data is stored in a Rectangle object. I have used a map instead of a RB tree since my RB tree did not fully function correctly. This was not finished due to time constraints.