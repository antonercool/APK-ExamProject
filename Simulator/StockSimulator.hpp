#pragma once
#include "Analyser/StockAnalyser.hpp"
#include "Loader/StockLoader.hpp"
#include <boost/signals2.hpp>
#include <ctime>
#include <random>
#include <string>
#include <thread>

namespace Simulator
{

class StockSimulator
{
  typedef boost::signals2::signal<void(std::vector<Stock> &)> SimulatorSignal;

public:
  StockSimulator();
  ~StockSimulator();

  StockSimulator(const Simulator::StockSimulator &stockSimulator);


  void start(std::vector<Stock> &stocks);
  
  template<typename T>
  const void attach(T & cb)
  {
    signal_.connect(cb); // Calls copy contructor of StockAnalyser, therefore the
                       // boost::signals2 analyseSignal_ in StockAnalyser must
                       // be heapyfied for Render::StockRender to connect to the
                       // excaty analyseSignal_ and not a copy
  }

private:
  std::vector<Stock> stocks_;
  SimulatorSignal    signal_;
  bool               firstTick_;

  void notify();
  void tick();
  void sleep(int milliseconds);
  void generateData(Stock &stock);
};

} // namespace Simulator