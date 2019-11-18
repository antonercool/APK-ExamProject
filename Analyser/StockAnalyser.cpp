#include "Analyser/StockAnalyser.hpp"

// REF: SØREN
// template <typename T>
// typename std::enable_if<std::is_trivially_copyable<T>::value>::type
// Copy(T *first, T *last, T *dest)
//{
//  memcpy(dest, first, sizeof(T) * (last-first));
//}
// template <typename T>
// typename std::enable_if<!std::is_trivially_copyable<T>::value>::type
// Copy(T *first, T *last, T *dest)
//{
//  for (; first != last; ++first, ++dest) *dest = *first;
//}

// Must be declared if not declared inline in StockAnalyser.cpp
// std::vector<Stock> Analyser::StockAnalyser::previousStockData_;

Analyser::StockAnalyser::StockAnalyser() {}
Analyser::StockAnalyser::~StockAnalyser() {}

const void Analyser::StockAnalyser::analyse(std::vector<Stock> stocks)
{

  if (previousStockData_.empty())
  {
  }
  else
  {
    Events::StockIsCrashedEvent crashedEvent = {stocks[0]};
    EventVariant eventVariant = crashedEvent;
    notify(eventVariant);
  }
  previousStockData_.clear();
  std::copy(stocks.begin(), stocks.end(),
            std::back_inserter(previousStockData_));

  std::cout << std::endl;
  for (Stock &stock : stocks)
  {
    std::cout << stock << std::endl;
  }
}

void Analyser::StockAnalyser::attach(
    const std::function<void(EventVariant)> &cb)
{
  analyserSignal_.connect(cb);
}

void Analyser::StockAnalyser::notify(EventVariant const &eventVariant)
{
  analyserSignal_(eventVariant);
}
