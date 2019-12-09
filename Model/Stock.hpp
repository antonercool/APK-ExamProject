#pragma once
#include <iostream>
#include <string>

class Stock
{

public:
  Stock(const std::string &name, const float &value, bool rising,
        unsigned int uncertainty, unsigned int percentageChange);

  Stock();

  //Stock(const Stock &stock);

  const std::string &getName() const;

  const float &getValue() const;

  void setValue(float value);

  const float &getStartValue() const;

  const bool &getRising() const;

  void setRising(bool isRising);

  const unsigned int &getUncertainty() const;

  const unsigned int &getPercentageChange() const;

  void setPercentageChange(const unsigned int percentage);

  friend std::istream &operator>>(std::istream &i, Stock &s);
  friend std::ostream &operator<<(std::ostream &o, const Stock &s);

private:
  std::string  name_;  
  float        value_;
  float        startValue_;
  bool         rising_;
  unsigned int uncertainty_;
  unsigned int percentageChange_;
};

std::ostream &operator<<(std::ostream &o, const Stock &s);

std::istream &operator>>(std::istream &i, Stock &s);