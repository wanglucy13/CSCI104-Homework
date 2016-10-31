#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include "board.h"
using namespace std;

Board::Board(){

}

Board::Board(int dim, int numInitMoves, int seed )
{
  _size = dim*dim;
  _tiles = new int[_size];
  srand(seed);
  for(int i=0; i < _size; i++){
    _tiles[i] = i;
  }
  int blankLoc = 0;
  while(numInitMoves > 0){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < _size){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      _tiles[blankLoc] = _tiles[randNeighbor];
      _tiles[randNeighbor] = 0;
      blankLoc = randNeighbor;
      numInitMoves--;
    }
  }
}

Board::~Board(){

}

Board::Board(const Board& other){
  _size = other.size();
  _tiles = new int[_size];
  for(int i = 0; i < _size; i++){
    _tiles[i] = other[i];
  }
}

void Board::move(int tile)
{
  int side_dim = dim();
  int tr, tc, br, bc;

  // find tile row and column
  int i=-1;
  while(_tiles[++i] != tile);

  tr = i / side_dim; 
  tc = i % side_dim;

  // find blank row and column
  int j=-1;
  while(_tiles[++j] != 0);

  br = j / side_dim;
  bc = j % side_dim;

  if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1){
    cout << "Invalid move of tile " << tile << " at ";
    cout << tr << "," << tc << " and blank spot at ";
    cout << br << "," << bc << endl;
    return;
  }
  // Swap tile and blank spot
  _tiles[j] = tile;
  _tiles[i] = 0;
}

// Generate new boards representing all the potential moves of tiles into 
// the current blank tile location. The returned map should have
// the key as the tile moved and the value as a new Board object with the
// configuration reflecting the move of that tile into the blank spot
map<int, Board*> Board::potentialMoves() const
{
  map<int, Board*> board;
  int blankTile;
  for(int i = 0; i < _size; i++){
    if(_tiles[i] == 0){
      blankTile = i;
    }
  }

  if((blankTile + 1)%dim() > blankTile%dim() && blankTile != dim()*dim()){
    Board* right = new Board(*this);
    right -> move(_tiles[blankTile + 1]);
    board.insert(make_pair(blankTile +1, right));
  }

  if((blankTile - 1)%dim() < blankTile%dim() && blankTile != 0){
    Board* left = new Board(*this);
    left -> move(_tiles[blankTile - 1]);
    board.insert(make_pair(blankTile -1, left));
  }

  if(blankTile >= dim()){
    Board* up = new Board(*this);
    if(blankTile - dim() >= 0){
      up -> move(_tiles[blankTile - dim()]);
      board.insert(make_pair(blankTile - dim(), up));
    }
  }

  if(blankTile < _size - dim()){
    Board* down = new Board(*this);
    if(blankTile + dim() <= dim()*dim()){
      down -> move(_tiles[blankTile + dim()]);
      board.insert(make_pair(blankTile + dim(), down));

    }
  }
  return board;
}

bool Board::solved() const{
  bool solved = true;
  for(int i = 0; i < _size; i++){
    if(_tiles[i] != i){
      solved = false;
    }
  }
  return solved;
}

std::ostream& operator<<(std::ostream &os, const Board &b){
  int side_dim = b.dim();
  b.printRowBanner(os);
  for(int i = 1; i <= side_dim * side_dim; i++){
    if(b[i - 1] == 0){
      os << "|" << setw(2) << "";
    }
    else{
      os << "|" << setw(2) << b[i - 1];
    }
      if(i%(side_dim) == 0){
        os << "|" << endl;
        b.printRowBanner(os); 
      }
  }
  return os;
}

bool Board::operator<(const Board& rhs) const{
  int size;
  if(this -> size() < rhs.size()){
    size = this -> size();
  }
  else{
    size = rhs.size();
  }

  for(int i = 0; i < size; i++){
    if(this -> _tiles[i] > rhs._tiles[i]){
      return false;
    }
    else return true;
  }
  return this -> size() < rhs.size();
}

const int& Board::operator[](int loc) const 
{ 
  return _tiles[loc]; 
}

int Board::size() const 
{ 
  return _size; 
}

int Board::dim() const
{
  return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const
{
  int side_dim = dim();
  if(side_dim == 0) return;
  os << "+";
  for(int i=0; i < side_dim; i++){
    os << "--+";
  }
  os << endl;
}
