#ifndef USER_H
#define USER_H
#include "review.h"
#include <iostream>
#include <string>
#include <vector>
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, std::string password);
  virtual ~User();

  int getAge() const;
  double getBalance() const;
  std::string getName() const;
  void deductAmount(double amt);
  std::string getPassword() const;
  virtual void dump(std::ostream& os);

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  std::string password_;
};
#endif
