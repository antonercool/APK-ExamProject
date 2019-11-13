#include <iostream>
#include <string>

class Stock
{

public:
  Stock(const std::string &name, const float &value, bool rising,
        unsigned int uncertainty, unsigned int percentageChange)
      : name_(name),
        value_(value),
        rising_(rising),
        uncertainty_(uncertainty),
        percentageChange_(percentageChange){};

  Stock()
      : name_(""),
        value_(0),
        rising_(false),
        uncertainty_(0),
        percentageChange_(0){};

  void calculateValue() const {}

  const std::string &getName() const { return name_; }

  void setName(std::string name) { name = name_; }

  const float &getValue() const { return value_; }

  void setValue(float value) { value = value_; }

  friend std::istream &operator>>(std::istream &i, Stock &s);
  friend std::ostream &operator<<(std::ostream &o, const Stock &s);

private:
  std::string name_;
  float       value_;

  bool         rising_;
  unsigned int uncertainty_;
  unsigned int percentageChange_;
};

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