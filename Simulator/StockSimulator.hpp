#pragma once
#include "Loader/StockLoader.hpp"
#include <boost/signals2.hpp>
#include <ctime>
#include <random>
#include <string>
#include <thread>

class StockSimulator
{
  typedef boost::signals2::signal<void(std::vector<Stock>)> SimulatorSignal;

public:
  StockSimulator(std::vector<Stock> &stocks)
  {
    stocks_ = stocks;

    srand(time(NULL));

    // for(Stock stock: *stocks){
    //    std::cout << stock << std::endl;
    //}
  };
  ~StockSimulator(){

  };

  void start()
  {
    // if (signal_.empty()) throw("No callbacks attatched");

    while (1)
    {
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      tick();
    }
  }

  void attach(const void (*cb)(std::vector<Stock>)) { 
    signal_.connect(cb);
    //std::cout << "attach raw pointer" << std::endl; 
  }
  void attach(const std::function<void(std::vector<Stock>)>& cb) {
    signal_.connect(cb);
    //std::cout << "attach std::function" << std::endl;
  }

  
  

private:
  StockLoader                                       stockLoader_;
  std::vector<Stock>                                stocks_;
  SimulatorSignal signal_;

  void notify(){
    signal_(stocks_);
  }
  
  void tick()
  {
    for (Stock &stock : stocks_)
    {
      generateData(stock);
    }

    notify();
  }

  void generateData(Stock &stock)
  {
    unsigned int ran = rand() % 100 + 1;
    if (stock.getUncertainty() >= ran) // Change rising state
    {
      stock.setRising(!stock.getRising());
    }

    float diff = stock.getStartValue() * ((float)stock.getPercentageChange() / 100);

    //std::cout << "Diff: " << stock.getStartValue() << std::endl;

    if (stock.getRising()) // Calculate new value
    {
      stock.setValue(stock.getValue() + diff);
    }
    else
    {
      stock.setValue(stock.getValue() - diff);
    }

    if(stock.getValue() < 1.0){ // Stock is crashed
      stock.setValue(0);
      stock.setPercentageChange(0);
    }
  }
};