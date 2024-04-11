#ifndef OWP_LIB_MONOMIAL_HPP_
#define OWP_LIB_MONOMIAL_HPP_

#include <set>
#include <string>
#include <vector>

class Monomial {
 public:
  Monomial(std::string s = "");
  Monomial(const Monomial &);
  ~Monomial();

  bool operator<(const Monomial &) const;
  bool operator<=(const Monomial &) const;
  bool operator==(const Monomial &) const;
  bool operator!=(const Monomial &) const;
  bool operator>=(const Monomial &) const;
  bool operator>(const Monomial &) const;
  Monomial operator-() const;
  Monomial &operator+=(const Monomial &);
  Monomial operator+(const Monomial &) const;
  Monomial &operator-=(const Monomial &);
  Monomial operator-(const Monomial &) const;
  Monomial &operator*=(const Monomial &);
  Monomial operator*(const Monomial &) const;
  Monomial &operator/=(const Monomial &);
  Monomial operator/(const Monomial &) const;

  bool isSimilar(const Monomial &monomial) const;

  std::string toString() const;

  std::set<char> var() const;
  double calculate_value(const std::vector<double> &) const;
  Monomial derivative(char) const;
  Monomial derivative(char, int) const;

  class InappropriateParameters : std::exception {
   public:
    std::string message() const;
  };
  class NotSpecified : std::exception {
   public:
    std::string message() const;
  };

 private:
  double coefficient_;
  std::vector<int> degrees_;
};

#endif  // OWP_LIB_MONOMIAL_HPP_