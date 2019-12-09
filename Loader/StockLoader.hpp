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
  std::vector<Stock> stockList_;

public:
  StockLoader();
  ~StockLoader();

  std::vector<Stock> &&loadStocks(std::string directory);
};
} // namespace Loader
