
#pragma once
#include "StockLoader.hpp"
#include <boost/signals2.hpp>
#include <string>
#include <thread>

class StockSimulator
{
public:
  StockSimulator()
  {
    stocks_ = stockLoader_.loadStocks("./stockDb");

    // for(Stock stock: *stocks){
    //    std::cout << stock << std::endl;
    //}
  };
  ~StockSimulator(){

  };

  void start()
  {
    if ( signal_.empty())
        throw ("No callbacks attatched");

    while (1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(5000));
      tick();
    }
  }

  void attach(void (*cb)(std::vector<Stock>)) { signal_.connect(cb); }

private:
  StockLoader                                       stockLoader_;
  std::vector<Stock> *                              stocks_;
  boost::signals2::signal<void(std::vector<Stock>)> signal_;

  // static void test(std::vector<Stock> t){}

  void tick()
  {

    // attach(test);
  }

  void generateData() {}
};