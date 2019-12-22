#pragma once
#include "IsSame/IsSame.hpp"
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
  void                            loadStocks(std::string &directory);

public:
  StockLoader();
  ~StockLoader();

  template <typename T, typename... Args>
  void loadStocks(T &arg, Args &... args)
  {
    static_assert(IsSame<T, std::string>::value,
                  "All arguments must be of type std::string");

    loadStocks(arg);
    loadStocks(args...);
  }
  std::vector<Stock> &&getStocks();
};
} // namespace Loader