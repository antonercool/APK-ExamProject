#include "Analyser/StockAnalyser.hpp"

Analyser::StockAnalyser::StockAnalyser()
    : analyserSignal_(new Analyser::AnalyserSignal)
{
}
Analyser::StockAnalyser::~StockAnalyser() {}
Analyser::StockAnalyser::StockAnalyser(
    const Analyser::StockAnalyser &stockAnalyser)
{
  previousStockData_ = stockAnalyser.previousStockData_;
  analyserSignal_    = stockAnalyser.analyserSignal_;
}

const void Analyser::StockAnalyser::analyse(const std::vector<Stock> &stocks)
{
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