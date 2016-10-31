#include "puzzle_heur.h"
#include <cmath>

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b){
	int dim = b.dim();
	int mDist = 0;
	int goal[dim*dim];
	int curr[dim*dim];
	for(int i = 0; i < dim*dim; i++){
		goal[i] = i;
		curr[i] = b[i];
	}
	for(int i = 0; i < dim*dim; i++){
		for(int j = 0; j < dim*dim; j++){
			if(curr[i] == goal[j] && i != j){
				mDist += (abs(i/dim - j/dim) + abs(i%dim - j%dim));
			}
		}
	}
	return mDist;
}

int PuzzleOutOfPlaceHeuristic::compute(const Board& b){
	int numOutOfPlace = 0;
	for(int i = 1; i < b.size(); i++){
		if (b[i] != i){
			numOutOfPlace++;
		}
	}
	return numOutOfPlace;
}

int PuzzleBFSHeuristic::compute(const Board& b){
	return 0;
}

