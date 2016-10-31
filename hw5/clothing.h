#ifndef CLOTHING_H 
#define CLOTHING_H
#include "datastore.h"
#include <string>
#include <fstream>

class Clothing : public Product{
public:
	Clothing(std::string brand, std::string size, const std::string category, 
		const std::string name, double price, int qty);
	~Clothing();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

	std::string getBrand();
	std::string getSize();

private:
	std::string brand_;
	std::string size_;
};
#endif