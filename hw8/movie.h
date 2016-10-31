#ifndef MOVIE_H
#define MOVIE_H
#include "datastore.h"
#include <string>
#include <fstream>

class Movie : public Product{
public:
	Movie(std::string genre, std::string rating, const std::string category, 
		const std::string name, double price, int qty);
	~Movie();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

	std::string getGenre();
	std::string getRating();

private:
	std::string genre_;
	std::string rating_;
};
#endif