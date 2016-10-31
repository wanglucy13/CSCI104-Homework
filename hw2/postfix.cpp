#include "stackdbl.h"
#include "llistdbl.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h> 

using namespace std;

double calculate(string& expr, bool& success);

int main(int argc, char* argv[]){
	ifstream ifile(argv[1]);
	if(ifile.fail()){ //checks if input is valid file
		cout << "Invalid file" << endl;
	}
	ofstream ofile(argv[2]);
	if(ofile.fail()){ //checks if output is valid file
		cout << "Invalid file" << endl;
	}
	string express;
	bool success = true;
	while(getline(ifile, express)){
		//creates double variable for the result of calculate function
		double value = calculate(express, success);
		if(success == true){
			ofile << value << '\n';
		}
		else {
			ofile << "invalid" << '\n';
			success = true;
		}
	}

	ifile.close();
	ofile.close();

}

double calculate(string& expr, bool& success){
	StackDbl stkdbl = StackDbl();
	double number = 0.0;
	string val;
	stringstream ss(expr);
	ss >> val;

	if(!ss.fail() && success){
		if(val == "+" || val == "-" || val == "*" || val == "/"){
			//checks if first value is an operator
			success = false;
			return 1.1;
		}
		else{
			number = atof(val.c_str());
			stkdbl.push(number);
			ss >> val;

			if(val == "+" || val == "-" || val == "*" || val == "/"){
				//checks if second value is an operator
				success = false;
				return 1.1;
			}
			else{
				number = atof(val.c_str());
				stkdbl.push(number);
				ss >> val;
				while(!ss.fail() && success && !stkdbl.empty()){
					if(val == "+"){
						//checks if value is + and adds previous numbers
						double n1 = stkdbl.top();
						stkdbl.pop();
						double n2 = stkdbl.top();
						stkdbl.pop();
						double add = n1 + n2;
						stkdbl.push(add);
						ss >> val;
					}
					else if(val == "-"){
						//checks if value is - and subtracts previous numbers
						double n1 = stkdbl.top();
						stkdbl.pop();
						double n2 = stkdbl.top();
						stkdbl.pop();
						double subtract = n2 - n1;
						stkdbl.push(subtract);
						ss >> val;
					}
					else if(val == "*" ){
						//checks if value is * and multiplies previous numbers
						double n1 = stkdbl.top();
						stkdbl.pop();
						double n2 = stkdbl.top();
						stkdbl.pop();
						double mult = n1 * n2;
						stkdbl.push(mult);
						ss >> val;
					}
					else if(val == "/"){
						//checks if value is / and divides previous numbers
						double n1 = stkdbl.top();
						stkdbl.pop();
						double n2 = stkdbl.top();	
						stkdbl.pop();
						double divide = n2/n1;
						stkdbl.push(divide);
						ss >> val;
					}
					else{
						//if val is not operator then push the number to stack
						number = atof(val.c_str());
						stkdbl.push(number);
						ss >> val;
					}
				}
			}		
		}	

		if(stkdbl.empty()){
			//if stack is empty then invalid expression
			success = false;
			return 1.1;
		}
		else{
			//if stack isn't then return the top val of stack
			return stkdbl.top();
		}

	}
	else{
		//if stack is empty or ss fails then expression is invalid
		success = false;
		return 1.1;
	}


	
}