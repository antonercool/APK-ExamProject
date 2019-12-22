#include "Render/StockRender.hpp"
#include "Render/UIProvider.hpp"
#include "Simulator/StockSimulator.hpp"
#include <boost/array.hpp>
#include <iostream>

struct X
{
  void operator()() { std::cout << "bla bla" << std::endl; }
};

template <typename T> 
struct has_function_operator
{
  typedef char operator_implemented;
  typedef long operator_not_implemented;

  // Hits this template function if type has implemented operator()
  //
  template <typename U>
  static operator_implemented check_for_operator(decltype(&U::operator()));

  // Trash can for all types without operator()
  template <typename U> static operator_not_implemented check_for_operator(...);

  // gives value either 1 or 0 decided from wether the check_for_operator
  // returns a char or a long
  // enum { value = sizeof(check_for_operator<T>(0)) == sizeof(char) };

  // The reason for passing 0 in the parameter is because it can be passed to a
  static const bool value = sizeof(check_for_operator<T>(0)) == sizeof(char);
};

template <typename T, typename A> 
auto attach(T &t, A &a)
{
  std::cout << "attach method" << std::endl;
  if constexpr (has_function_operator<T>::value)    // stockSimulator.attach(stockAnalyser)
  {
    std::cout << "den har function operator" << std::endl;
    std::function<void(std::vector<Stock>)> callback = t;
    a.attach(callback);
  }
  else                                               // stockAnalyser.attach(render)
  {
    std::function<void(Analyser::EventVariant)> callback = boost::bind(&T::callback, &t, _1);
    a.attach(callback);
    std::cout << "Ingen functions og men der er attach methoder" << std::endl;
  }
}

int main()
{
  Render::UIProvider cmdRender;

  Loader::StockLoader stockLoader;
  std::vector<Stock>  stocks;
  try
  {
    stocks = stockLoader.loadStocks("./stockDb");
  }
  catch (boost::filesystem::filesystem_error &e)
  {
    std::cout << "Bad directory. Handle this..." << std::endl;
    throw;
  }
  catch (Loader::NoStocksException &e)
  {
    std::cout << "No stocks. Handle this..." << std::endl;
    throw;
  }
  catch (...)
  {
    std::cout << "Unknown exception." << std::endl;
    throw;
  }

  Simulator::StockSimulator stockSimulator(stocks);
  Analyser::StockAnalyser   stockAnalyser /*(stockSimulator)*/;

  // stockSimulator.attach(stockAnalyser); // Attaching StockAnalyser as a
  // functor
  attach(stockAnalyser, stockSimulator);

  Render::StockRender stockRender(&cmdRender);
  
  // vi bliver nødt til at ligge boost::bind funktionen over i en variabel for at give den med til attach()
  // da boost::bind er en R-value og vi skal give en L value med til typename. 
  //auto cb = boost::bind(&Render::StockRender::callback, &stockRender, _1);
  attach(stockRender, stockAnalyser);

  // stockAnalyser.attach(boost::bind(
  //    &Render::StockRender::render, &stockRender,
  //    _1)); // Attaching Render::StockRender::render using boost::bind
  
  stockSimulator.start();

  return 0;
}