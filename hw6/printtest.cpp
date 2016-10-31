#include <iostream>
#include <iomanip>

using namespace std;



void printRowBanner()
{
  int side_dim = 4;
  if(side_dim == 0) return;
  cout << "+";
  for(int i=0; i < side_dim; i++){
    cout << "--+";
  }
  cout << endl;
}

void print(){
  int side_dim = 4;
  printRowBanner(); 
  for(int i = 1; i <= side_dim * side_dim; i++){
    if(i - 1 == 0){
      cout << "|" << setw(2) << "";
    }
    else cout << "|" << setw(2) << i - 1;
    if(i%(side_dim) == 0){
      cout << "|" << endl;
      printRowBanner(); 
    }
  }
}
 
 int main(){
	print();
}