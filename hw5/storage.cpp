#include "storage.h"
#include "datastore.h"
#include "util.h"
#include "book.h"
#include "product.h"
#include "movie.h"
#include "clothing.h"
#include "review.h"
#include <vector>
#include <map>
#include <set>
#include <string>
//#include <deque>
#include <iostream>

Storage::Storage(){

}

Storage::~Storage(){

}

void Storage::addProduct(Product* p){
	products_.push_back(p);
	std::set<std::string> keywords = p -> keywords();
	//creates a set of string for keywords to be used in search
	for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
			std::set<Product*> newSet;
			keywordMap[*it] = newSet;
			keywordMap[*it].insert(p);
	}
}

void Storage::addUser(User* u){
	users_.push_back(u);
}

std::vector<Product*> Storage::search(std::vector<std::string>& terms, int type){
	std::set<Product*> newSet = keywordMap[terms[0]];
	//adds the first term of the set into a new set
	std::set<Product*> newSet2;
	for(unsigned int i = 1; i < terms.size(); i++){
		//if there are remaining terms, add them into a new set
		newSet2 = keywordMap[terms[i]];
		if(type == 0){
			//if user types AND then set intersection 
			newSet = setIntersection(newSet, newSet2);
		}
		else if(type == 1){
			//if user types OR then set union
			newSet = setUnion(newSet, newSet2);
		}
	}
	for(std::set<Product*>::iterator it = newSet.begin(); it != newSet.end(); it++){
		//push all elements from set into a new vector to be returned in the function
		prodHits.push_back(*it);
	}



	return prodHits;
}

User* Storage::findUser(std::string name){
	//function to find users with the username as a parameter
	User* temp = NULL;
	for(unsigned int i = 0; i < users_.size(); i++){
		if(convToLower(name) == users_[i] -> getName()){
			temp = users_[i];
		}
	}
	return temp;
}

void Storage::addCart(std::string name, std::vector<Product*> hits, int hitNum){
	//finds the user to add products to their cart
	User* user = findUser(name);
	std::vector<Product*> productHits;
	if(cartMap.find(user) == cartMap.end()){
		//makes sure the product is in the map
		if(hits[hitNum - 1] -> getQty() != 0){
			//if the product is not out of stock then add to the dequq
			productHits.push_back(hits[hitNum - 1]);
		}
		//else do nothing
		else return;
	}
	else{
		if(hits[hitNum - 1] -> getQty() != 0){
			productHits = cartMap[user];
			productHits.push_back(hits[hitNum - 1]);
		}
		else return;
	}
	//sets the products in the cart to the user in the map
	cartMap[user] = productHits;
}

void Storage::viewCart(std::string name){
	User* user = findUser(name);
	std::vector<Product*> temp = cartMap[user];
	for(unsigned int i = 0; i < temp.size(); i++){
		std::cout << "Item " << i + 1 << std::endl;
		std::cout << temp[i] -> displayString();
	}
}

void Storage::buyCart(std::string name){
	User* user = findUser(name);
	std::vector<Product*> temp = cartMap[user];

	for(unsigned int i = 0; i < temp.size(); i++){
		double money = user -> getBalance();
		double price = temp[i] -> getPrice();
		int quanity = temp[i] -> getQty();
		if(money >= price && quanity > 0){
			//if user has enough money and the item is in stock
			//subtract one from the quantity and deduct the user's balance
			temp[i] -> subtractQty(1);
			user -> deductAmount(price);
		}
	}

}

void Storage::dump(std::ostream& ofile){
	ofile << "<products>" << std::endl;
	for(unsigned int i = 0; i < products_.size(); i++){
		products_[i] -> dump(ofile);
	}
	ofile << "</products>" << std::endl;
	ofile << "<users>" << std::endl;
	for(unsigned int i = 0; i < users_.size(); i++){
		users_[i] -> dump(ofile);
	}
	ofile << "</users>" << std::endl;
	ofile << "<reviews>" << std::endl;
	std::map<Product*, std::vector<Review*> >::iterator it;
	for(it = reviews.begin(); it != reviews.end(); ++it){
		for(unsigned int i = 0; i < (it -> second).size(); i++){
			ofile << (it -> first) -> getName() << std::endl;
    		ofile << (it -> second)[i] -> rating << " ";
    		ofile << (it -> second)[i] -> date << " ";
    		ofile << (it -> second)[i] -> reviewText << " " << std::endl;
		}
	}
	ofile << "</reviews>" << std::endl;
}

void Storage::addReview(Review* r){
	std::string name = r -> prodName;
	Product* product;
	for(unsigned int i = 0; i < products_.size(); i++){
		if(name == products_[i] -> getName()){
			product = products_[i];
		}
	}
	std::vector<Review*> prodReviews;
	if(reviews.find(product) == reviews.end()){
		prodReviews.push_back(r);
	}
	else{
		prodReviews = reviews[product];
		prodReviews.push_back(r);
	}
	reviews[product] = prodReviews; 
}

std::vector<User*> Storage::getUser(){
	return users_;
}

std::vector<Product*> Storage::getProduct(){
	return products_;
}

std::map<Product*, std::vector<Review*> >  Storage::getReview(){
	return reviews;
}

std::map<User*, std::vector<Product*> > Storage::getCart() {
	return cartMap;
}

std::vector<Product*> Storage::getProductHits(){
	return prodHits;
}

void Storage::updateReviews(Product* p, Review* r){
	std::vector<Review*> temp = reviews[p];
	temp.push_back(r);
	reviews[p] = temp;
}

void Storage::updateCart(User* u, std::vector<Product*> p){
	cartMap[u] = p;
}

void Storage::updateProducts(std::vector<Product*> p){
	prodHits = p;
}
