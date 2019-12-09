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

Analyser::StockAnalyser::StockAnalyser()
    : analyserSignal_(new Analyser::AnalyserSignal)
{
  // stockSimulator.attach(boost::bind(&Analyser::StockAnalyser::analyse, this,
  // _1));
}
Analyser::StockAnalyser::~StockAnalyser() {}
Analyser::StockAnalyser::StockAnalyser(
    const Analyser::StockAnalyser &stockAnalyser)
{
  //std::cout << "This is analyser copyConstruct" << std::endl;
  previousStockData_ = stockAnalyser.previousStockData_;
  analyserSignal_    = stockAnalyser.analyserSignal_;
}

const void Analyser::StockAnalyser::analyse(const std::vector<Stock> &stocks)
{
  //std::cout << std::endl;
  //for (Stock stock : stocks)
  //{
  //  std::cout << stock << std::endl;
  //}

  if (!previousStockData_.empty())
  {
    for (size_t i = 0; i < stocks.size(); i++)
    {
      RaiseEventIfRising(previousStockData_[i], stocks[i]);
      RaiseEventIfFalling(previousStockData_[i], stocks[i]);
      RaiseEventIfDoubled(stocks[i]);
      RaiseEventIfHalved(stocks[i]);
      RaiseEventIfCrashed(stocks[i]);
    }    
  }

  previousStockData_.clear();
  std::copy(stocks.begin(), stocks.end(),
            std::back_inserter(previousStockData_));  
}

void Analyser::StockAnalyser::RaiseEventIfRising(const Stock &previousStock,
                                                 const Stock &updatedStock)
{
  if (previousStock.getValue() < updatedStock.getValue())
  {
    notify(
        createEvent(Events::Event::StockValueIsRisingEventEnum, updatedStock));
  }
}

void Analyser::StockAnalyser::RaiseEventIfFalling(const Stock &previousStock,
                                                  const Stock &updatedStock)
{
  if (previousStock.getValue() > updatedStock.getValue())
  {
    notify(
        createEvent(Events::Event::StockValueIsFallingEventEnum, updatedStock));
  }
}

void Analyser::StockAnalyser::RaiseEventIfDoubled(const Stock &updatedStock)
{
  if (updatedStock.getStartValue() * 2 <= updatedStock.getValue())
  {
    notify(
        createEvent(Events::Event::StockValueIsDoubledFromStartValueEventEnum,
                    updatedStock));
  }
}

void Analyser::StockAnalyser::RaiseEventIfHalved(const Stock &updatedStock)
{
  if (updatedStock.getStartValue() / 2 >= updatedStock.getValue())
  {
    notify(createEvent(Events::Event::StockValueIsHalvedFromStartValueEventEnum,
                       updatedStock));
  }
}

void Analyser::StockAnalyser::RaiseEventIfCrashed(const Stock &updatedStock)
{
  if (updatedStock.getValue() <= 0)
  {
    notify(createEvent(Events::Event::StockIsCrashedEventEnum, updatedStock));
  }
}

const void Analyser::StockAnalyser::operator()(const std::vector<Stock> &stocks)
{
  analyse(stocks);
}

 

void Analyser::StockAnalyser::notify(EventVariant const &eventVariant)
{
  //std::cout << "Analyser notify: " << analyserSignal_.get() << std::endl;
  (*(analyserSignal_))(eventVariant);
}

Analyser::EventVariant
Analyser::StockAnalyser::createEvent(const Events::Event event,
                                     const Stock &       stock)
{
  switch (event)
  {
  case Events::Event::StockValueIsRisingEventEnum:
  {
    Events::StockValueIsRisingEvent event = {stock};
    return event;
    break;
  }
  case Events::Event::StockValueIsFallingEventEnum:
  {
    Events::StockValueIsFallingEvent event = {stock};
    return event;
    break;
  }
  case Events::Event::StockValueIsDoubledFromStartValueEventEnum:
  {
    Events::StockValueIsDoubledFromStartValueEvent event = {stock};
    return event;
    break;
  }
  case Events::Event::StockValueIsHalvedFromStartValueEventEnum:
  {
    Events::StockValueIsHalvedFromStartValueEvent event = {stock};
    return event;
    break;
  }
  case Events::Event::StockIsCrashedEventEnum:
  {
    Events::StockIsCrashedEvent event = {stock};
    return event;
    break;
  }
  default:
  {
    break;
  }
    
  
  }
}