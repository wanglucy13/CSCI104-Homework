#ifndef REVIEW_H
#define REVIEW_H
#include <string>

/**
 * Models a review for the product identified by prodName
 */
struct Review
{
  Review() :  prodName(), rating(), user(), date(), reviewText()
  { }
  Review(std::string& prod, 
	 int& rate, 
   std::string& username,
	 std::string& d, 
	 std::string& review_text) :
    prodName(prod), 
    rating(rate), 
    user(username),
    date(d), 
    reviewText(review_text)
  { }
  
  std::string prodName;
  int rating;
  std::string user;
  std::string date;
  std::string reviewText;
};

#endif
