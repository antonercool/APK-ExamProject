#include "Model/Stock.hpp"
#include <iostream>
#include <string>


Stock::Stock()
    : name_(""),
      value_(0),
      startValue_(0),
      rising_(false),
      uncertainty_(0),
      percentageChange_(0){};

const std::string &Stock::getName() const { return name_; }

const float &Stock::getValue() const { return value_; }

void Stock::setValue(float value) { value_ = value; }

const float &Stock::getStartValue() const { return startValue_; }

const bool &Stock::getRising() const { return rising_; }

void Stock::setRising(bool isRising) { rising_ = isRising; }

const unsigned int &Stock::getUncertainty() const { return uncertainty_; }

const unsigned int &Stock::getPercentageChange() const
{
  return percentageChange_;
}

void Stock::setPercentageChange(const unsigned int percentage)
{
  percentageChange_ = percentage;
}

std::ostream &operator<<(std::ostream &o, const Stock &s)
{
  return o << s.name_ << " " << s.value_ << " " << s.rising_ << " "
           << s.uncertainty_ << " " << s.percentageChange_;
}

std::istream &operator>>(std::istream &i, Stock &s)
{
  i >> s.name_ >> s.value_ >> s.rising_ >> s.uncertainty_ >>
      s.percentageChange_;

  s.startValue_ = s.value_;

  return i;
}