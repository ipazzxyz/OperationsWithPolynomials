#include "polynomial.h"

#include "validator.h"

Polynomial::Polynomial(std::string s) {
  Validator validator(s);
  int i = 0;
  for (int j = std::min(s.find('+', 1), s.find('-', 1)); j != std::string::npos;
       i = j, j = std::min(s.find('+', j + 1), s.find('-', j + 1))) {
    data_->push_front(Monomial(s.substr(i, j - i)));
  }
  data_->push_front(Monomial(s.substr(i)));
  normalize();
  return;
}
Polynomial::Polynomial(const Polynomial &polynomial) {
  *this = polynomial;
  return;
}
Polynomial::~Polynomial() {
  delete data_;
  return;
}

Polynomial &Polynomial::operator=(const Polynomial &polynomial) {
  for (Node<Monomial> *it = polynomial.data_->first(); it; it = it->next()) {
    data_->push_back(it->data());
  }
  return *this;
}
bool Polynomial::operator==(const Polynomial &polynomial) const {
  for (Node<Monomial> *it1 = data_->first(), *it2 = polynomial.data_->first();
       it1 && it2; it1 = it1->next(), it2 = it2->next()) {
    if (it1->data() != it2->data()) {
      return false;
    }
  }
  return true;
}
Polynomial &Polynomial::operator+=(const Polynomial &polynomial) {
  for (Node<Monomial> *it = polynomial.data_->first(); it; it = it->next()) {
    data_->push_back(it->data());
  }
  normalize();
  return *this;
}
Polynomial Polynomial::operator+(const Polynomial &polynomial) const {
  return Polynomial(*this) += polynomial;
}
Polynomial &Polynomial::operator-=(const Polynomial &polynomial) {
  for (Node<Monomial> *it = polynomial.data_->first(); it; it = it->next()) {
    data_->push_back(-it->data());
  }
  normalize();
  return *this;
}
Polynomial Polynomial::operator-(const Polynomial &polynomial) const {
  return Polynomial(*this) -= polynomial;
}
Polynomial &Polynomial::operator*=(const Polynomial &polynomial) {
  return *this = *this * polynomial;
}
Polynomial Polynomial::operator*(const Polynomial &polynomial) const {
  Polynomial result;
  for (Node<Monomial> *it1 = data_->first(); it1; it1 = it1->next()) {
    for (Node<Monomial> *it2 = polynomial.data_->first(); it2;
         it2 = it2->next()) {
      result.data_->push_front(it1->data() * it2->data());
    }
  }
  result.normalize();
  return result;
}
Polynomial Polynomial::operator/=(const Polynomial &polynomial) {
  std::pair<Polynomial, Polynomial> result = *this / polynomial;
  *this = result.first;
  return result.second;
}
std::pair<Polynomial, Polynomial> Polynomial::operator/(
    const Polynomial &divisor) const {
  if (divisor.many_vars() || this->many_vars()) {
    throw CannotApplyFunction();
  }
  Polynomial quotient, remainder(*this);
  Monomial leadingTermDivisor = divisor.data_->last()->data();
  while (!remainder.data_->empty() &&
         remainder.data_->last()->data() >= leadingTermDivisor) {
    Monomial leadingTermRemainder = remainder.data_->last()->data();
    Monomial quotientTerm = leadingTermRemainder / leadingTermDivisor;
    Polynomial temp;
    temp.data_->push_front(quotientTerm);
    quotient += temp;
    Polynomial subtrahend = divisor * temp;
    remainder -= subtrahend;
  }
  return std::make_pair(quotient, remainder);
}

std::string Polynomial::toString() const {
  if (data_->empty()) {
    return "0";
  }
  Node<Monomial> *it = data_->first();
  std::string s = it->data().toString();
  for (it = it->next(); it; it = it->next()) {
    std::string addition = it->data().toString();
    if (addition[0] != '+' && addition[0] != '-') {
      s += "+";
    }
    s += addition;
  }
  return s;
}

std::set<char> Polynomial::var() const {
  std::set<char> result;
  for (Node<Monomial> *it = data_->first(); it; it = it->next()) {
    std::set<char> temp = it->data().var();
    result.insert(temp.begin(), temp.end());
  }
  return result;
}
double Polynomial::calculate_value(const std::vector<double> &var) const {
  double result = 0;
  for (Node<Monomial> *it = data_->first(); it; it = it->next()) {
    result += it->data().calculate_value(var);
  }
  return result;
}
std::set<int> Polynomial::int_roots() const {
  std::set<char> vars = var();
  if (vars.size() > 1) {
    throw CannotApplyFunction();
  }
  int i = *vars.begin() - 'a';
  std::set<int> result;
  std::vector<double> v(26, 0);
  for (v[i] = -10000; v[i] <= 10000; ++v[i]) {
    if (calculate_value(v) == 0) {
      result.insert(v[i]);
    }
  }
  return result;
}
Polynomial Polynomial::derivative(char c) const { return derivative(c, 1); }
Polynomial Polynomial::derivative(char c, int n) const {
  Polynomial result;
  for (Node<Monomial> *it = data_->first(); it; it = it->next()) {
    result.data_->push_back(it->data().derivative(c, n));
  }
  result.normalize();
  return result;
}

std::string Polynomial::CannotApplyFunction::message() const {
  return "Нельзя применить функцию к многочлену с таким количеством "
         "переменных";
}

bool Polynomial::many_vars() const { return var().size() > 1; }
void Polynomial::normalize() {
  qsort(data_->first(), data_->last());
  sum_similar();
  erase_zeros();
}
void Polynomial::sum_similar() {
  if (data_->empty()) {
    return;
  }
  for (Node<Monomial> *it1 = data_->first(), *it2 = data_->first()->next(); it2;
       it2 = it2->next()) {
    if (it1->data().isSimilar(it2->data())) {
      it1->data() += it2->data();
      it2->data() = Monomial();
    } else {
      it1 = it2;
    }
  }
  return;
}
void Polynomial::erase_zeros() {
  Node<Monomial> *it = data_->first();
  while (it) {
    Node<Monomial> *buffer = it;
    it = it->next();
    if (buffer->data() == Monomial()) {
      data_->erase(buffer);
    }
  }
  return;
}