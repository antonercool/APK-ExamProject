#pragma once
#include "Model/Stock.hpp"
#include <boost/filesystem.hpp>
#include <exception>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace Loader
{

struct NoStocksException : public std::exception
{
  const char *what() const throw()
  {
    return "No futures created, stock directory could be empty.";
  }
};

class StockLoader
{
private:
  std::vector<Stock>              stockList_;
  void                            addFutureToWaitingList(std::future<Stock> &&);
  std::vector<std::future<Stock>> futures_;

public:
  StockLoader();
  ~StockLoader();

  void                            loadStocks(std::string &directory);
  template <typename... T> 
  void loadStocks(std::string &arg, T &... args)
  {
    loadStocks(arg);
    loadStocks(args...);
  }
  std::vector<Stock> &&getStocks();
};
} // namespace Loader
