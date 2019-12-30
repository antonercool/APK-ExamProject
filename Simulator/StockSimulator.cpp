#include "Simulator/StockSimulator.hpp"

Simulator::StockSimulator::StockSimulator() : firstTick_(true)
{
  srand(time(NULL));
};
Simulator::StockSimulator::~StockSimulator(){

};
Simulator::StockSimulator::StockSimulator(
    const Simulator::StockSimulator &stockSimulator)
{
}

void Simulator::StockSimulator::start(std::vector<Stock> &stocks)
{
  stocks_ = stocks;
   if (signal_.empty()) throw("No callbacks attatched");

  while (1)
  {
    tick();
    sleep(2000);
  }
}

void Simulator::StockSimulator::sleep(int milliseconds)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void Simulator::StockSimulator::notify() { signal_(stocks_); }

void Simulator::StockSimulator::tick()
{
  if (!firstTick_)
  {
    for (Stock &stock : stocks_)
    {
      generateData(stock);
    }
  }

  firstTick_ = false;

  notify();
}

void Simulator::StockSimulator::generateData(Stock &stock)
{
  unsigned int ran = rand() % 100 + 1;
  if (stock.getUncertainty() >= ran) // Change rising state
  {
    stock.setRising(!stock.getRising());
  }

  float diff =
      stock.getStartValue() * ((float)stock.getPercentageChange() / 100);

  if (stock.getRising()) // Calculate new value
  {
    stock.setValue(stock.getValue() + diff);
  }
  else
  {
    stock.setValue(stock.getValue() - diff);
  }

  if (stock.getValue() < 1.0) // Stock is crashed
  {
    stock.setValue(0);
    stock.setPercentageChange(0);
  }
}
