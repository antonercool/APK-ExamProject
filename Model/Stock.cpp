#include "Stock.hpp"
#include <iostream>
#include <string>

Stock::Stock(const std::string &name, const float &value, bool rising,
             unsigned int uncertainty, unsigned int percentageChange)
    : name_(name),
      value_(value),
      rising_(rising),
      uncertainty_(uncertainty),
      percentageChange_(percentageChange){};

Stock::Stock()
    : name_(""),
      value_(0),
      rising_(false),
      uncertainty_(0),
      percentageChange_(0){};

const std::string &Stock::getName() const { return name_; }

void Stock::setName(std::string name) { name_ = name; }

const float &Stock::getValue() const { return value_; }

void Stock::setValue(float value) { value_ = value; }

const bool &Stock::getRising() const { return rising_; }

void Stock::setRising(bool isRising) { rising_ = isRising; }

const unsigned int &Stock::getUncertainty() const { return uncertainty_; }

const unsigned int &Stock::getPercentageChange() const { return percentageChange_; }

std::ostream &operator<<(std::ostream &o, const Stock &s)
{
  return o << s.name_ << " " << s.value_ << " " << s.rising_ << " "
           << s.uncertainty_ << " " << s.percentageChange_;
}

std::istream &operator>>(std::istream &i, Stock &s)
{
  return i >> s.name_ >> s.value_ >> s.rising_ >> s.uncertainty_ >>
         s.percentageChange_;
}