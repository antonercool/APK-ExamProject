#include "Loader/StockLoader.hpp"

namespace fs = boost::filesystem;

Loader::StockLoader::StockLoader(){

};

Loader::StockLoader::~StockLoader(){

};

std::vector<Stock> &&Loader::StockLoader::loadStocks(std::string directory)
{
  stockList_.clear();
  std::vector<std::future<Stock>> futures;

  fs::path               path   = directory;
  fs::directory_iterator dir_it = fs::directory_iterator(
      path); // If this throws, exception is caught in main.cpp

  for (const auto &entry : dir_it)
  {
    std::promise<Stock> p;
    std::future<Stock>  f = p.get_future();
    futures.push_back(
        std::move(f)); // std::future is not CopyConsructable or Assignable ->
                       // Move future resource to vector

    std::thread(
        [&, entry](std::promise<Stock> &&p) {
          std::ifstream stockFile(entry.path());
          Stock         s = *std::istream_iterator<Stock>(
              stockFile); // Constructor reads first line in db-file using
                          // operator>>, dereference returns current stream
                          // element

          p.set_value(s);
          stockFile.close();
        },
        std::move(p)) // Sharing a std::promise between two threads is bad, the
                      // resource must have unique ownership -> Move promise to
                      // thead function
        .detach();
  }

  if (futures.empty())
  {
    throw NoStocksException();
  }

  // Using swap to implement a strong guarentee where we make the possibly
  // exception throwing operations on a temp-list where we afterwards swaps
  // the temp-list into our stocklist. (swap is a no-throw guarentee function)
  std::vector<Stock> tempStockList(stockList_);

  for (std::future<Stock> &future : futures)
  {
    future.wait();
    tempStockList.push_back(future.get());
  }
  stockList_.swap(tempStockList);

  return std::move(stockList_);
}