#include "Attacher/Attacher.hpp"
#include "Render/StockRender.hpp"
#include "Render/UIProvider.hpp"
#include "Simulator/StockSimulator.hpp"
#include <boost/array.hpp>
#include <iostream>

int main()
{
  std::vector<Stock>  stocks;
  Loader::StockLoader stockLoader;

  try
  {
    std::string aStocksDb = "./aStocksDb", bStocksDb = "./bStocksDb",
                cStocksDb = "./cStocksDb";

    stockLoader.loadStocks(aStocksDb, bStocksDb, cStocksDb);
    stocks = stockLoader.getStocks();
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

  Simulator::StockSimulator stockSimulator;
  Analyser::StockAnalyser   stockAnalyser;

  Attacher::attach(stockAnalyser,
                   stockSimulator); // Attaching StockAnalyser as a functor

  Render::UIProvider  cmdRender;
  Render::StockRender stockRender(&cmdRender);

  Attacher::attach(stockRender,
                   stockAnalyser); // Attaching StockRender callback

  stockSimulator.start(stocks);

  return 0;
}