#pragma once
#include "StockLoader/StockLoader.hpp"
#include <boost/signals2.hpp>
#include <ctime>
#include <random>
#include <string>
#include <thread>

class StockSimulator
{
public:
  StockSimulator()
  {
    stocks_ = stockLoader_.loadStocks("./stockDb");

    srand(time(NULL));

    // for(Stock stock: *stocks){
    //    std::cout << stock << std::endl;
    //}
  };
  ~StockSimulator(){

  };

  void start()
  {
    //if (signal_.empty()) throw("No callbacks attatched");

    while (1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      tick();
    }
  }

  void attach(void (*cb)(std::vector<Stock>)) { signal_.connect(cb); }

private:
  StockLoader                                       stockLoader_;
  std::vector<Stock>                                stocks_;
  boost::signals2::signal<void(std::vector<Stock>)> signal_;

  // static void test(std::vector<Stock> t){}
  // attach(test);

  void tick()
  {
    for (Stock &stock : stocks_)
    {
      generateData(stock);
    }

    for (Stock &stock : stocks_)
    {
      std::cout << stock << std::endl;
    }

  }

  void generateData(Stock &stock)
  {
    unsigned int ran = rand() % 100 + 1;
    if (stock.getUncertainty() >= ran) // Change rising state
    {
      stock.setRising(!stock.getRising());
    }

    float diff = stock.getValue() * ((float)stock.getPercentageChange() / 100);

    //std::cout << "Diff: " << diff << std::endl;
 
    if (stock.getRising()) // Calculate new value
    {
      stock.setValue(stock.getValue() + diff);
    }
    else
    {
      stock.setValue(stock.getValue() - diff);
    }
  }
};