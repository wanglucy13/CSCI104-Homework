#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

struct Rectangle {
    int ID;
    int length;
    int height;
};
//global variables
int** board;
map<int, Rectangle*> rectMap;
map<int, pair<int, int> >& solution;
//prototypes
void solverHelper(map<int, Rectangle*>::iterator& it);

void puzzleSolver(map<int, Rectangle*>::iterator& it);

bool isValid(int row, int col);

int main(int argc, char *argv[]){
	if(argc < 3){
		cerr << "Usage: ./rectangle input.txt output.text" << endl;
		return 1;
	}
	int length, height, numTiles, numID, li, hi;
	//initialize variables 

	ifstream ifile(argv[1]);
	ofstream ofile(argv[2]);

	if(ifile.fail()){ //checks if input is valid file
		cout << "Invalid file" << endl;
		return -1;
	}
	if(ofile.fail()){ //checks if output is valid file
		cout << "Invalid file" << endl;
		return -1;
	}

	ifile >> length >> height >> numTiles;

	vector<int> vectorID;
	vector<Rectangle*> vectorRect;

	board = new int*[length * height];
	for(int i = 0; i < height; i++){
		for(int j = 0; j < length; j++){
			board[i][j] = -1; 
		}
	}

	for(int i = 0; i < numTiles; i++){
		ifile >> numID >> li >> hi;
		Rectangle* rect = new Rectangle();
		rect -> ID  = numID;
		rect -> length = li;
		rect -> height = hi;
		vectorID.push_back(rect -> ID);
		vectorRect.push_back(rect);
		ofile << "no solution found" << endl;
	}

	map<int, Rectangle*> rectMap;
	for(unsigned int i = 0; i < vectorID.size(); i++){
		rectMap[vectorID[i]] = vectorRect[i];

	}

	/*start at lower left hand corner

	*/
}

bool isValid(int row, int col){
	int val = board[row][col];

	for (int i=0; i<row; i++) {
		if (i == row) {
			continue;
		}

		int temp = board[i][col];
		if (temp != -1) {
			return false;
		}
	}

	for (int i=0; i<9; i++) {
		if (i == col) {
			continue;
		}

		int temp = board[row][i];
		if (temp == val) {
			return false;
		}
	}
  
  return true;
}

void puzzleSolver(map<int, Rectangle*>::iterator& it){

}

void solverHelper(map<int, Rectangle*>::iterator& it){
	if(it == rectMap.end()){
		return;
	}
}
