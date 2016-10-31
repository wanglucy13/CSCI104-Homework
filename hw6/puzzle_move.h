#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include "board.h"

using namespace std;

struct PuzzleMove
{
  // Data members can be public
  int tileMove;  // tile moved to reach the Board b
  Board *b;      // Pointer to a board representing the updated state
  int g;         // distance from the start board
  int h;         // heuristic distance to the goal
  int f;
  PuzzleMove *prev;  // Pointer to parent PuzzleMove


  // Constructor for starting Board (i.e. initial move)
  PuzzleMove(Board* board);

  // Constructor for subsequent search boards 
  // (i.e. those returned by Board::potentialMoves() )
  PuzzleMove(int tile, Board* board, PuzzleMove *parent);

  // Destructor
  ~PuzzleMove();

};

struct PuzzleMoveScoreComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {

    if(m1 -> f > m2 -> f){
      return false; 
  
    }

    else if(m1 -> f == m2 -> f){
      if(m1 -> h > m2 -> h){
        return false;
      }
    }

    return m1 -> f < m2 -> f;
  }
};

struct PuzzleMoveBoardComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {

    Board* boardm1 = m1 -> b;
    Board* boardm2 = m2 -> b;

   

    return *boardm1 < *boardm2;



  }
};

#endif
