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
  typedef boost::signals2::signal<void(std::vector<Stock>&)> SimulatorSignal;

public:
  StockSimulator(std::vector<Stock> &stocks);
  ~StockSimulator();

  StockSimulator(const Simulator::StockSimulator &stockSimulator);


  void start();
  const void attach(const Analyser::StockAnalyser &cb);

private:
  std::vector<Stock> stocks_;
  SimulatorSignal    signal_;
  bool firstTick_;

  void notify();
  void tick();
  void generateData(Stock &stock);
};

} // namespace Simulator