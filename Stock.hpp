#include <string>
#include <iostream>


class Stock
{
private:
    std::string name_;
    int value_;

    bool rising_;
    int uncertainty_;
    int percentageChange_;    

public:
    Stock(){

    };
    ~Stock(){
        
    };

    void calculateValue() const {

    }

    const std::string& getName() const{
        return name_;
    }

    void setName(std::string name){
        name = name_;
    }

    const int& getValue() const{
        return value_;
    }

    void setValue(int value){
        value = value_;
    }

    friend std::istream& operator>> ( std::istream& i, Stock& s );
    friend std::ostream& operator<< ( std::ostream& o, const Stock& s );
};


std::ostream& operator<< ( std::ostream& o, const Stock& s )
{ 
  return o << s.name_ << " " << s.value_ << " " << s.rising_ << " " << s.uncertainty_ << " " << s.percentageChange_; 
}

std::istream& operator>> ( std::istream& i, Stock& s )
{
    return i >> s.name_ >> s.value_ >> s.rising_ >> s.uncertainty_ >> s.percentageChange_;
}