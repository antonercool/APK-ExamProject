#pragma once
#include <boost/filesystem.hpp>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class StockLoader
{
private:
  std::vector<Stock> stockList_;

public:
  StockLoader(){

  };
  ~StockLoader(){

  };

  std::vector<Stock> *loadStocks(std::string directory)
  {
    stockList_.clear();
    std::vector<std::future<Stock>> futures;

    boost::filesystem::path path = directory;
    for (const auto &entry : boost::filesystem::directory_iterator(path))
    {
      std::promise<Stock> p;
      std::future<Stock>  f = p.get_future();
      futures.push_back(std::move(f)); // Move future resource to vector

      std::thread(
          [entry](std::promise<Stock> p) {
            std::ifstream stockFile(entry.path());
            Stock         s = *std::istream_iterator<Stock>(
                stockFile); // Constructor reads first line in db-file using
                            // operator>>, dereference returns current stream
                            // element

            p.set_value(s);
            stockFile.close();
          },
          std::move(p)) // Move promise to thead function
          .detach();
    }

    for (std::future<Stock> &future : futures)
    {
      future.wait();
      stockList_.push_back(future.get());
    }

    return &stockList_;
  }
};