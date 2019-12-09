#include "Loader/StockLoader.hpp"

Loader::StockLoader::StockLoader(){

};

Loader::StockLoader::~StockLoader(){

};

// Only created for 'Perfect forwarding'
 void Loader::StockLoader::addFutureToWaitingList(std::future<Stock> && future){
     futures_.push_back(std::forward<std::future<Stock>>(future));

     // future get treated at l value  // future not copyable // deleted function error
     //futures_.push_back(future);

 }

std::vector<Stock> &&Loader::StockLoader::loadStocks(std::string directory)
{
  stockList_.clear();

  boost::filesystem::path               path = directory;
  boost::filesystem::directory_iterator dir_it =
      boost::filesystem::directory_iterator(
          path); // If this throws, exception is caught in main.cpp

  for (const auto &entry : dir_it)
  {
    std::promise<Stock> p;
    std::future<Stock>  f = p.get_future();
    
    addFutureToWaitingList(std::move(f));
    
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

  if (futures_.empty())
  {
    throw NoStocksException();
  }

  // Using swap to implement a strong guarentee where we make the possibly
  // exception throwing operations on a temp-list where we afterwards swaps
  // the temp-list into our stocklist. (swap is a no-throw guarentee function)
  std::vector<Stock> tempStockList(stockList_);

  for (std::future<Stock> &future : futures_)
  {
    future.wait();
    tempStockList.push_back(future.get());
  }
  stockList_.swap(tempStockList);

  return std::move(stockList_);
}