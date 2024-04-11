#include "monomial.h"

inline double pow(double x, int n) {
  if (n == 0) {
    return 1;
  }
  if (n % 2 == 0) {
    return pow(x * x, n / 2);
  }
  return x * pow(x, n - 1);
}

Monomial::Monomial(std::string s) : coefficient_(0), degrees_(26, 0) {
  if (s.size() == 0) {
    return;
  }
  bool negative = s[0] == '-';
  int i = 0;
  if (s[0] == '+' || s[0] == '-') {
    i = 1;
  }
  if (!isdigit(s[i])) {
    coefficient_ = -2 * negative + 1;
  }
  while (i < s.size() && isdigit(s[i])) {
    coefficient_ = coefficient_ * 10 + (s[i++] - '0') * (negative * -2 + 1);
  }
  if (coefficient_ == 0) {
    return;
  }
  for (; i < s.size(); ++i) {
    int variable = s[i] - 'a';
    if (i + 1 >= s.size() || s[i + 1] != '^') {
      ++degrees_[variable];
      continue;
    }
    int buffer = degrees_[variable];
    degrees_[variable] = 0;
    i += 2;
    for (i; i < s.size() && isdigit(s[i]); ++i) {
      degrees_[variable] = degrees_[variable] * 10 + s[i] - '0';
    }
    --i;
    degrees_[variable] += buffer;
  }
}
Monomial::Monomial(const Monomial &monomial)
    : coefficient_(monomial.coefficient_), degrees_(monomial.degrees_) {}
Monomial::~Monomial() {}

bool Monomial::operator<(const Monomial &monomial) const {
  for (int i = 0; i < 26; ++i) {
    if (degrees_[i] < monomial.degrees_[i]) {
      return true;
    }
    if (degrees_[i] > monomial.degrees_[i]) {
      return false;
    }
  }
  return coefficient_ < monomial.coefficient_;
}
bool Monomial::operator<=(const Monomial &monomial) const {
  return !(*this > monomial);
}
bool Monomial::operator==(const Monomial &monomial) const {
  for (int i = 0; i < 26; ++i) {
    if (degrees_[i] != monomial.degrees_[i]) {
      return false;
    }
  }
  return coefficient_ == monomial.coefficient_;
}
bool Monomial::operator!=(const Monomial &monomial) const {
  return !(*this == monomial);
}
bool Monomial::operator>=(const Monomial &monomial) const {
  return !(*this < monomial);
}
bool Monomial::operator>(const Monomial &monomial) const {
  return !(((*this) == monomial) || (*this) > monomial);
}
Monomial Monomial::operator-() const {
  Monomial result(*this);
  result.coefficient_ *= -1;
  return result;
}
Monomial &Monomial::operator+=(const Monomial &monomial) {
  coefficient_ += monomial.coefficient_;
  if (coefficient_ == 0) {
    std::fill(degrees_.begin(), degrees_.end(), 0);
  }
  return *this;
}
Monomial Monomial::operator+(const Monomial &monomial) const {
  return Monomial(*this) += monomial;
}
Monomial Monomial::operator-(const Monomial &monomial) const {
  return Monomial(*this) -= monomial;
}
Monomial &Monomial::operator-=(const Monomial &monomial) {
  coefficient_ -= monomial.coefficient_;
  if (coefficient_ == 0) {
    std::fill(degrees_.begin(), degrees_.end(), 0);
  }
  return *this;
}
Monomial &Monomial::operator*=(const Monomial &monomial) {
  coefficient_ *= monomial.coefficient_;
  if (coefficient_ == 0) {
    std::fill(degrees_.begin(), degrees_.end(), 0);
    return *this;
  }
  for (int i = 0; i < 26; ++i) {
    degrees_[i] += monomial.degrees_[i];
  }
  return *this;
}
Monomial Monomial::operator*(const Monomial &monomial) const {
  return Monomial(*this) *= monomial;
}
Monomial &Monomial::operator/=(const Monomial &monomial) {
  coefficient_ /= monomial.coefficient_;
  if (coefficient_ == 0) {
    std::fill(degrees_.begin(), degrees_.end(), 0);
    return *this;
  }
  for (int i = 0; i < 26; ++i) {
    degrees_[i] += monomial.degrees_[i];
  }
  return *this;
}
Monomial Monomial::operator/(const Monomial &monomial) const {
  return Monomial(*this) /= monomial;
}

bool Monomial::isSimilar(const Monomial &monomial) const {
  for (int i = 0; i < 26; ++i) {
    if (degrees_[i] != monomial.degrees_[i]) {
      return false;
    }
  }
  return true;
}

std::string Monomial::toString() const {
  if (coefficient_ == 0) {
    return "0";
  }
  std::string s;
  if (coefficient_ == -1) {
    s += '-';
  } else if (coefficient_ != 1) {
    s += std::to_string(static_cast<int>(coefficient_));
  }
  for (int i = 0; i < 26; ++i) {
    if (!degrees_[i]) {
      continue;
    }
    if (degrees_[i] == 1) {
      s += i + 'a';
      continue;
    }
    s += std::string(1, 'a' + i) + "^" + std::to_string(degrees_[i]);
  }
  if (s.empty()) {
    return "1";
  }
  if (s == "-") {
    return "-1";
  }
  return s;
}

std::set<char> Monomial::var() const {
  std::set<char> result;
  for (int i = 0; i < 26; ++i) {
    if (degrees_[i]) {
      result.insert(i + 'a');
    }
  }
  return result;
}
double Monomial::calculate_value(const std::vector<double> &var) const {
  double result = coefficient_;
  for (int i = 0; i < 26; ++i) {
    result *= pow(var[i], degrees_[i]);
  }
  return result;
}
Monomial Monomial::derivative(char c) const {
  Monomial result;
  if (isSimilar(result)) {
    return result;
  }
  int tmp = c - 'a';
  result.coefficient_ = coefficient_ * degrees_[tmp];
  result.degrees_[tmp] = degrees_[tmp] - 1;
  return result;
}
Monomial Monomial::derivative(char c, int n) const {
  Monomial result = derivative(c);
  for (int i = 1; i < n; ++i) {
    result = result.derivative(c);
  }
  return result;
}