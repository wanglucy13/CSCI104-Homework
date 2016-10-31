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

private:
	std::vector<User*> users_;
	std::vector<Product*> products_;
	std::map<std::string, std::set<Product*> > keywordMap;
	std::map<User*, std::deque<Product*> > cartMap;

};
#endif