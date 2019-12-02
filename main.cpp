#include "Render/StockRender.hpp"
#include "Render/UIProvider.hpp"
#include "Simulator/StockSimulator.hpp"
#include <boost/array.hpp>
#include <iostream>

struct X
{
  void operator()() { std::cout << "bla bla" << std::endl; }
};

template<typename T>
struct has_function_operator{
    typedef char operator_implemented;
    typedef long operator_not_implemented;

    // Hits this template function if type has implemented operator()
    // 
    template<typename U> 
    static operator_implemented check_for_operator(decltype (&U::operator()));

    // Trash can for all types without operator()
    template<typename U> 
    static operator_not_implemented check_for_operator(...);

    // gives value either 1 or 0 decided from wether the check_for_operator returns a char or a long
    //enum { value = sizeof(check_for_operator<T>(0)) == sizeof(char) };

    // The reason for passing 0 in the parameter is because it can be passed to a
    static const bool value = sizeof(check_for_operator<T>(0)) == sizeof(char);
};

template<typename T>
auto attach(T t){
    if constexpr(has_function_operator<T>::value){
        std::cout << "den har function operator" << std::endl;
    }
    else {
        std::cout << "den har IKKE function operator" << std::endl;
    }
}

int main()
{

  Render::UIProvider cmdRender;

  cmdRender.setColor(Render::Color::BLUE);
  cmdRender.print("This should be blue\n");

  cmdRender.setColor(Render::Color::RED);
  cmdRender.print("This should be red\n");

  cmdRender.setColor(Render::Color::GREEN);
  cmdRender.print("This should be Green\n");

  cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld\n");
  cmdRender.resetToDefaultColor();
  cmdRender.print("This should have default color\n");

  StockLoader        stockLoader;
  std::vector<Stock> stocks = stockLoader.loadStocks("./stockDb");

  Simulator::StockSimulator stockSimulator(stocks);
  Analyser::StockAnalyser   stockAnalyser /*(stockSimulator)*/;

  stockSimulator.attach(stockAnalyser); // Attaching StockAnalyser as a functor

  Render::StockRender stockRender;
  stockAnalyser.attach(boost::bind(&Render::StockRender::render, &stockRender, _1)); // Attaching Render::StockRender::render using boost::bind
  //stockSimulator.start();

  // getchar();
    
    attach(stockAnalyser);
    attach(stockRender);
    std::cout << has_function_operator<Analyser::StockAnalyser>::value << std::endl;    //print 1
    std::cout << has_function_operator<Render::StockRender>::value << std::endl;  //print 0
    return 0;
}