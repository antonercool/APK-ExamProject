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
  typedef boost::signals2::signal<void(std::vector<Stock>)> SimulatorSignal;

public:
  StockSimulator(std::vector<Stock> &stocks);
  ~StockSimulator();

  void start();
  void attach(Analyser::StockAnalyser cb);

private:
  StockLoader        stockLoader_;
  std::vector<Stock> stocks_;
  SimulatorSignal    signal_;

  void notify();
  void tick();
  void generateData(Stock &stock);
};

} // namespace Simulator