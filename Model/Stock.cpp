#include "Model/Stock.hpp"
#include <iostream>
#include <string>

// Stock::Stock(const std::string &name, const float &value, bool rising,
//             unsigned int uncertainty, unsigned int percentageChange)
//    : name_(name),
//      value_(value),
//      startValue_(value),
//      rising_(rising),
//      uncertainty_(uncertainty),
//      percentageChange_(percentageChange){};

Stock::Stock()
    : name_(""),
      value_(0),
      startValue_(0),
      rising_(false),
      uncertainty_(0),
      percentageChange_(0){};

const std::string &Stock::getName() const { return name_; }

//Stock::Stock(const Stock &stock)
//{
//  name_ = stock.name_;
//  value_ = stock.value_;
//  startValue_ = stock.startValue_;
//  rising_ = stock.rising_;
//  uncertainty_ = stock.uncertainty_;
//  percentageChange_ = stock.percentageChange_;
//  std::cout << "Stock copyConstructor: " << name_ << std::endl;
//}

// void Stock::setName(std::string name) { name_ = name; }

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