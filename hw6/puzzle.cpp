#include <iostream>
#include <cstdlib>
#include <deque>
#include <sstream>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"

int main(int argc, char *argv[])
{
	if(argc < 5){
		cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
	return 1;
	}

	int n, initMoves, heur, seed, input;

	n = atoi(argv[1]);
	initMoves = atoi(argv[2]);
	seed = atoi(argv[3]);
	heur = atoi(argv[4]); 

	Board* b = new Board(n, initMoves, seed);
	PuzzleHeuristic* ph;

	if(heur == 0){
		ph = new PuzzleBFSHeuristic();
	}
	else if(heur == 1){
		ph = new PuzzleOutOfPlaceHeuristic();
	}
	else if(heur == 2){
		ph = new PuzzleManhattanHeuristic();
	}

	PuzzleSolver* ps = new PuzzleSolver(*b, ph);
	deque<int> sol;
	cout << *b << endl;


	cout << "Enter tile number to move or -1 for a cheat: ";
	while(!cin.fail()){
		cin >> input;
		if(input == -1){
			cout << "Try this sequence:" << endl;
			ps -> run();
			sol = ps -> getSolution();
			for(unsigned int i = 0; i < sol.size(); i++){
				if(sol[i] != sol[i + 1] && sol[i] > 0){
					cout << sol[i] << " ";
				}
			}
			cout << endl << "(Expansions = " << ps -> getNumExpansions() << ")" << endl;
			cout << *b << endl;

		}
		else if(input == 0){
			return -1;
		}
		else if(input > 0 && input < n * n){
			b -> move(input);
			cout << *b << endl;
			if(b -> solved()){
				cout << "YOU WIN" << endl;
				return 0;
			}

		}
	}



	// n = argv[1];
	// initMoves = argv[2];
	// seed = argv[3];
	// heur = argv[4];

	/* 
	If the user enters a valid tile number then move the tile and 
	go on to the next turn
	If the user enters 0, cleanup and quit the program
	If the user enters -1, run the A* algorithm, and displaying the solution sequence
	and statistics, then go on to the next turn
	*/






  return 0;
}
