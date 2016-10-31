#include "puzzle_solver.h"
#include "heap.h"
#include <functional>

// Constructor (makes a copy of the Board and stores it in b_)
//  Also takes a PuzzleHeuristic which will score boards
PuzzleSolver::PuzzleSolver(){

}

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph){
	_b = b;
	_ph = ph;
	_expansions = 0;

}

// Destructor
PuzzleSolver::~PuzzleSolver(){

}

void PuzzleSolver::run(){
	PuzzleMove* pm = new PuzzleMove(&_b);
	PuzzleMoveScoreComp scoreComp;
	PuzzleMoveSet close;
	Heap<PuzzleMove*, PuzzleMoveScoreComp> openlist(2, scoreComp);
	openlist.push(pm);
	close.insert(pm);
	_expansions++;

	while(!openlist.empty()){
		PuzzleMove* move = openlist.top();
		move -> h = _ph -> compute(*move -> b);
		move -> f = move -> g + move -> h;

		openlist.pop();

		if((move -> b) -> solved()){
			for(set<PuzzleMove*, PuzzleMoveBoardComp>::iterator
				it = close.begin(); it != close.end(); ++it){
				PuzzleMove* sol = *it;
				if(sol -> prev != NULL){
					sol = sol -> prev;
					_solution.push_front(sol -> tileMove);
				}
			}
			return;
		}

		else{
			map<int, Board*> moves;
			moves = (move -> b) -> potentialMoves();
			for(map<int, Board*>::iterator it = moves.begin(); it != moves.end(); ++it){
				PuzzleMove* next = new PuzzleMove(it -> first, it -> second, move);
				next -> h = _ph -> compute(*next -> b);
				next -> f = next -> g + next -> h;

				if(close.find(next) == close.end() && close.find(move) == close.end()){
					openlist.push(next);
					close.insert(move);
					_expansions++;
				}
			}
		}
		

	}
}

// Return the solution deque
std::deque<int> PuzzleSolver::getSolution(){
	return _solution;
}

// Return how many expansions were performed in the search
int PuzzleSolver::getNumExpansions(){
	return _expansions;
}