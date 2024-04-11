#ifndef OWP_LIB_POLYNOMIAL_H_
#define OWP_LIB_POLYNOMIAL_H_

#include <exception>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "list.h"
#include "monomial.h"

class Polynomial {
 public:
  Polynomial(std::string s = "");
  Polynomial(const Polynomial&);
  ~Polynomial();

  Polynomial& operator=(const Polynomial&);
  bool operator==(const Polynomial&) const;
  Polynomial& operator+=(const Polynomial&);
  Polynomial operator+(const Polynomial&) const;
  Polynomial& operator-=(const Polynomial&);
  Polynomial operator-(const Polynomial&) const;
  Polynomial& operator*=(const Polynomial&);
  Polynomial operator*(const Polynomial&) const;
  Polynomial operator/=(const Polynomial&);
  std::pair<Polynomial, Polynomial> operator/(const Polynomial&) const;

  std::string toString() const;

  std::set<char> var() const;
  double calculate_value(const std::vector<double>&) const;
  std::set<int> int_roots() const;
  Polynomial derivative(char c) const;
  Polynomial derivative(char c, int n) const;

  class CannotApplyFunction : std::exception {
   public:
    std::string message() const;
  };

 private:
  List<Monomial>* data_ = new List<Monomial>;

  bool many_vars() const;
  void normalize();
  void sum_similar();
  void erase_zeros();
};

#endif  // OWP_LIB_POLYNOMIAL_H_