#include "movie.h"
#include "datastore.h"
#include "util.h"
#include <string>
#include <set>
#include <sstream>
#include <iostream>	
#include <fstream>

Movie::Movie(std::string genre, std::string rating, const std::string category, 
	const std::string name, double price, int qty):Product(category, 
	name, price, qty){
	genre_ = genre;
	rating_ = rating;
}

Movie::~Movie(){

}

std::set<std::string> Movie::keywords() const{
	std::set<std::string> keySet = parseStringToWords(name_);
	keySet.insert(convToLower(genre_));
	//inserts genre into set
	return keySet;
}

std::string Movie::displayString() const{
	std::stringstream ss;
    ss << price_;
	std::string moviePrice = ss.str();
    std::stringstream ss2;
    ss2 << qty_;
	std::string quanity = ss2.str();
	std::string movieString = name_ + "\n" + "Genre: " + genre_ + " Rating: "
		+ rating_ + "\n" + moviePrice + " " + quanity + " left.\n";
	return movieString;
}

void Movie::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << genre_ << std::endl;
	os << rating_ << std::endl;
}

std::string Movie::getRating(){
	return rating_;
}

std::string Movie::getGenre(){
	return genre_;
}
