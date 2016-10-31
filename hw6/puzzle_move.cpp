#include "puzzle_move.h"

/* 
Used as the primary data that the A* search algorithm uses. 
Stores a board, the g and h scores, a pointer to its parent move in
the search tree, and the tile value that was slid to arrive at this move.
*/

PuzzleMove::PuzzleMove(Board* board){
	b = board;
	prev = NULL;
	tileMove = -1;
	g = 0;
	h = 0;
	f = 0;
}

PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent){
	prev = parent;
	b = board;
	tileMove = tile;	
	g = (prev -> g) + 1;
	h = 0;
	f = g + h;
}

PuzzleMove::~PuzzleMove(){

}