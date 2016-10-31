#include "book.h"
#include "datastore.h"
#include "util.h"
#include <string>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>

Book::Book(std::string isbn, std::string author, const std::string category, 
	const std::string name, double price, int qty):Product(category, 
	name, price, qty){
	isbn_ = isbn;
	author_ = author;
}

Book::~Book(){

}

std::set<std::string> Book::keywords() const{
	std::set<std::string> authorSet = parseStringToWords(author_);
	std::set<std::string> titleSet = parseStringToWords(name_);
	std::set<std::string> unionSet = setUnion(authorSet, titleSet);
	unionSet.insert(isbn_);
	return unionSet;
}

std::string Book::displayString() const{
	std::stringstream ss;
    ss << price_;
	std::string bookPrice = ss.str();
	std::stringstream ss2;
    ss2 << qty_;
	std::string quanity = ss2.str();
	std::string bookString = name_ + "\n" + "Author: " + author_ + " ISBN: "
		+ isbn_ + "\n" + bookPrice + " " + quanity + " left.\n";
	return bookString;
}

void Book::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << isbn_ << std::endl;
	os << author_ << std::endl;
}

std::string Book::getISBN(){
	return isbn_;
}

std::string Book::getName(){
	return author_;
}
