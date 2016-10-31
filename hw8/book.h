#ifndef BOOK_H 
#define BOOK_H
#include "datastore.h"
#include <string>
#include <fstream>

class Book : public Product{
public:
	Book(std::string isbn_, std::string author_, const std::string category, 
		const std::string name, double price, int qty);
	~Book();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

	std::string getISBN();
	std::string getName();

private:
	std::string isbn_;
	std::string author_;
};
#endif