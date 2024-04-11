#ifndef OWP_LIB_VALIDATOR_H_
#define OWP_LIB_VALIDATOR_H_

#include <exception>
#include <string>
#include <vector>

class Validator {
 public:
  Validator(std::string);
  class BadFormat : std::exception {
   public:
    BadFormat(int);
    std::string what();

   private:
    int index_;
  };

 private:
  enum state {
    error,
    initial,
    after_sign,
    after_first_digit,
    after_coefficient,
    after_pow,
  };
  enum signal {
    unknown,
    digit_zero,
    digit_not_zero,
    sign,
    variable,
    pow_symbol,
  };
  state state_;
  std::vector<std::vector<state>> fsm_ =
      std::vector<std::vector<state>>(6, std::vector<state>(6, error));

  void init_map();
  signal get_signal(char c);
};

#endif