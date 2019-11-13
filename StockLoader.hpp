#include <boost/filesystem.hpp>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

namespace fs = boost::filesystem;

class StockLoader
{
private:
  std::vector<Stock> stockList_;

public:
  StockLoader(){

  };
  ~StockLoader(){

  };

  std::vector<Stock>* loadStocks(std::string directory)
  {
    //std::vector<Stock> stockList_;
    stockList_.clear();

    std::vector<std::future<Stock>> futures;

    boost::filesystem::path path = directory;
    for (const auto &entry : boost::filesystem::directory_iterator(path))
    {
      std::promise<Stock> p;
      std::future<Stock>  f = p.get_future();
      futures.push_back(std::move(f));

      std::thread(
          [entry](std::promise<Stock> p) {
            std::ifstream stockFile(entry.path().c_str());
            Stock         s = *std::istream_iterator<Stock>(stockFile);

            p.set_value(s);
            stockFile.close();
          },
          std::move(p))
          .detach();
    }

    //for (std::future<Stock> const &future : futures)
    //{
    //  future.wait();
    //}

    for (std::future<Stock> &future : futures)
    {
        future.wait();
        stockList_.push_back(future.get());
      //std::cout << future.get() << std::endl;
    }

    return &stockList_;
  }
};