#include "validator.h"

Validator::Validator(std::string s) : state_(initial) {
  init_map();
  for (int i = 0; i < s.size(); ++i) {
    state_ = fsm_[state_][get_signal(s[i])];
    if (state_ == error) {
      throw BadFormat(i);
    }
  }
  if (state_ == after_sign || state_ == after_pow) {
    throw BadFormat(s.size());
  }
}

void Validator::init_map() {
  fsm_[initial][digit_not_zero] = after_first_digit,
  fsm_[initial][sign] = after_sign, fsm_[initial][variable] = after_coefficient,

  fsm_[after_sign][digit_not_zero] = after_first_digit,
  fsm_[after_sign][variable] = after_coefficient,

  fsm_[after_first_digit][digit_zero] = after_first_digit,
  fsm_[after_first_digit][digit_not_zero] = after_first_digit,
  fsm_[after_first_digit][sign] = after_sign,
  fsm_[after_first_digit][variable] = after_coefficient,

  fsm_[after_coefficient][sign] = after_sign,
  fsm_[after_coefficient][variable] = after_coefficient,
  fsm_[after_coefficient][pow_symbol] = after_pow,

  fsm_[after_pow][digit_not_zero] = after_first_digit;

  return;
}
Validator::signal Validator::get_signal(char c) {
  if (isdigit(c)) {
    return digit_not_zero;
  }
  if (c == '+' || c == '-') {
    return sign;
  }
  if (c >= 'a' && c <= 'z') {
    return variable;
  }
  if (c == '^') {
    return pow_symbol;
  }
  return unknown;
}

Validator::BadFormat::BadFormat(int index) : index_(index) {}
std::string Validator::BadFormat::what() {
  return "Недопустимый символ на позиции " + std::to_string(index_);
}