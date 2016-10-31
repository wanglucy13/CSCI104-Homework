#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <string>
#include <set>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

std::set<std::string> punctHelperFunction(std::string word){
	//helper function to fund punctuation the returns the set of words
	int pos = word.length()-1;
	bool punct = false;
	std::set<std::string> words;
	for(unsigned int i = word.length() - 1; i > 0; i--){
		if(ispunct(word[i])){	//if there is punctuation in the word
			//remove the punctuation and add it to the set
			word = word.substr(i+1, pos);
			punct = true;
		}
	}
	if(!punct && word.length() >= 2){
		words.insert(word);
	}

	return words;
}

std::set<std::string> parseStringToWords(string rawWord){
	set<string> words;
	string word;
	stringstream ss(rawWord);
	ss >> word;

	while(!ss.fail()){
		word = convToLower(word);
		if(word.length() <= 1)
			//if the word length is less then 2 then go to next word
			ss >> word;
		else if(word.length() >= 2){
			//if word length is greater or equal to 2 then call helper
			std::set<std::string> newSet = punctHelperFunction(word);
			//combine the union of the two sets together
			words = setUnion(words, newSet);
		}
		//get new word
		ss >> word;
	}	
	return words;
}
