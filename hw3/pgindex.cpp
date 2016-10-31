#include "llistint.h"
#include "setint.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

bool existsPunct(string &lineWord);
void insertSet(int page, map<string, SetInt> &map, string &word, SetInt &set);
void printMap(map<string, SetInt> map, int page);


int main(int argc, char* argv[]){	
	if(argc < 2){	//check for arguments
		cout << "Please enter an input and output file" << endl;
		return -1;
	}

	map<string, SetInt> wordMap;
	int pagenum = 1;

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

	string line;

	while(getline(ifile, line)){
		string word;
		stringstream ss(line);
		ss >> word;

		while(!ss.fail()){
			if(word == "<pagebreak>"){ //search if word is pagebreak
				pagenum++;	//increment page number
			}
			else{
				while(ispunct(word[0])){ //sees if first element is a punct
					string temp = "";
					for(unsigned int i = 0; i < word.length() - 1; i++){
						temp[i] = word[i+1];
					}
					word = temp;
				}

				while (ispunct(word[word.length()-1])){
					string temp = "";
					for(unsigned int i = 0; i < word.length() - 2; i++){
						temp[i] = word[i];
					}
				}

				if(word.length() >= 2){ //checks if word is >= than 2 char
					if(!existsPunct(word)){
						SetInt pageSet;
						insertSet(pagenum, wordMap, word, pageSet); 
					}
					else{
						int hyphenPos = word.length()-1;
						for(unsigned int i = word.length()-2; i >0; i--){
							if(word[i] == '-'){ //checks if there is hyphen
								string subWord = word.substr(i+1, hyphenPos);
								SetInt pageSet;
								if(!existsPunct(subWord)){
									insertSet(pagenum, wordMap, subWord, pageSet);
								}
							}
						}
					}
				}
			}
			ss >> word;
		}
	}

	for(int i = 3; i < argc; i++){ //goes through all words in command line
		string argvWord = argv[i];
		for(unsigned int j = 0; j < argvWord.length(); j++){
			argvWord[j] = tolower(argvWord[j]);
		}
		if(wordMap.find(argvWord) == wordMap.end()){ //checks if word is in map
			ofile << "None" << endl;
		}
		else{
			SetInt pageSet = wordMap[argvWord];
			ofile << *(pageSet.first());
			for(unsigned int j = pageSet.size()-2; j > 0; j--){
				ofile << *(pageSet.next());
			}
		}
	}

	ofile.close();
	ifile.close();
	return 0;
}


bool existsPunct(string &word){ //function that checks for punctuation
	bool isPunct = false;
	for(unsigned int i = 0; i < word.length(); i++){
		word[i] = tolower(word[i]); //sets characters to lower case
		if(ispunct(word[i])){
			isPunct = true;
		}
	}
	return isPunct;
}

void insertSet(int page, map<string, SetInt> &map, string &word, SetInt &set){
	if(map.find(word) == map.end()){
		set.insert(page); //inserts page num into set
		map[word] = set; //inserts set into map
	}
	else{
		set = map[word];
		set.insert(page);
		map[word] = set;
	}
}
