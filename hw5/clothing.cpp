#include "clothing.h"
#include "datastore.h"
#include "util.h"
#include <string>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>

Clothing::Clothing(std::string brand, std::string size, const std::string category, 
	const std::string name, double price, int qty):Product(category, 
	name, price, qty){
	brand_ = brand;
	size_ = size;
}

Clothing::~Clothing(){

}

std::set<std::string> Clothing::keywords() const{
	std::set<std::string> brand = parseStringToWords(brand_);
	return brand;
}

std::string Clothing::displayString() const{
	std::stringstream ss;
    ss << price_;
	std::string clothingPrice = ss.str();
    std::stringstream ss2;
    ss2 << qty_;
	std::string quanity = ss2.str();
	std::string clothingString = name_ + "\n" + "Brand: " + brand_ + 
		" Size: " + size_ + "\n" + clothingPrice + " " + quanity + " left.\n";
	return clothingString;
}

void Clothing::dump(std::ostream& os) const{
	os << category_ << std::endl;
	os << name_ << std::endl;
	os << price_ << std::endl;
	os << qty_ << std::endl;
	os << size_ << std::endl;
	os << brand_ << std::endl;
}

std::string Clothing::getBrand(){
	return brand_;
}

std::string Clothing::getSize(){
	return size_;
}
