#include "Simulator/StockSimulator.hpp"

Simulator::StockSimulator::StockSimulator(std::vector<Stock> &stocks)
    : firstTick_(true)
{
  stocks_ = stocks;

  srand(time(NULL));

  // for(Stock stock: *stocks){
  //    std::cout << stock << std::endl;
  //}
};
Simulator::StockSimulator::~StockSimulator(){

};
Simulator::StockSimulator::StockSimulator(const Simulator::StockSimulator &stockSimulator)
{
}

void Simulator::StockSimulator::start()
{
  // if (signal_.empty()) throw("No callbacks attatched");

  while (1)
  {
    tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  }
}

// void attach(const void (*cb)(std::vector<Stock>)) {
//  signal_.connect(cb);
//  //std::cout << "attach raw pointer" << std::endl;
//}
// void attach(const std::function<void(std::vector<Stock>&)>& cb) {
//  signal_.connect(cb);
//  //std::cout << "attach std::function" << std::endl;
//}

const void Simulator::StockSimulator::attach( std::function<void(std::vector<Stock>)> & cb)
{

 // std::function<void(std::vector<Stock>)> test = cb;

  signal_.connect(cb); // Calls copy contructor of StockAnalyser, therefore the
                       // boost::signals2 analyseSignal_ in StockAnalyser must
                       // be heapyfied for Render::StockRender to connect to the
                       // excaty analyseSignal_ and not a copy
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

  // std::cout << "Diff: " << stock.getStartValue() << std::endl;

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
