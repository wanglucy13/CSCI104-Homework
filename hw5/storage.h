#ifndef STORAGE_H
#define STORAGE_H
#include "datastore.h"
#include "product.h"
#include <vector>
#include <deque>
#include <set>
#include <map>

class Storage: public DataStore{
public: 
	Storage();
	~Storage();
	void addProduct(Product* p);
	void addUser(User* u);
	std::vector<Product*> search(std::vector<std::string>& terms, int type);
	void dump(std::ostream& ofile);
	User* findUser(std::string name);
	void addCart(std::string name, std::vector<Product*> hits, int hitNum);
	void viewCart(std::string name);
	void buyCart(std::string name);
	void addReview(Review* r);
	std::vector<User*> getUser();
	std::vector<Product*> getProduct();
	std::map<Product*, std::vector<Review*> > getReview();
	std::map<User*, std::vector<Product*> > getCart();
	std::vector<Product*> getProductHits();
	void updateReviews(Product* p, Review* r);
	void updateCart(User* u, std::vector<Product*> p);
	void updateProducts(std::vector<Product*> p);

private:
	std::vector<User*> users_;
	std::vector<Product*> products_;
	std::map<std::string, std::set<Product*> > keywordMap;
	std::map<User*, std::vector<Product*> > cartMap;
	std::map<Product*, std::vector<Review*> > reviews;
	std::vector<Product*> prodHits;
};
#endif