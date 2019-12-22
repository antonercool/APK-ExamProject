#include "HasFunctionOperator/HasFunctionOperator.hpp"
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
  Analyser::StockAnalyser   stockAnalyser /*(stockSimulator)*/;

  // stockSimulator.attach(stockAnalyser); // Attaching StockAnalyser as a
  // functor
  HasFunctionOperator::attach(stockAnalyser, stockSimulator);

  Render::UIProvider  cmdRender;
  Render::StockRender stockRender(&cmdRender);

  // vi bliver nødt til at ligge boost::bind funktionen over i en variabel for
  // at give den med til attach() da boost::bind er en R-value og vi skal give
  // en L value med til typename.
  // auto cb = boost::bind(&Render::StockRender::callback, &stockRender, _1);
  HasFunctionOperator::attach(stockRender, stockAnalyser);

  // stockAnalyser.attach(boost::bind(
  //    &Render::StockRender::render, &stockRender,
  //    _1)); // Attaching Render::StockRender::render using boost::bind

  stockSimulator.start(stocks);

  return 0;
}