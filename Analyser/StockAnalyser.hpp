#pragma once
#include "Events/StockEvents.hpp"
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

namespace Analyser
{
typedef std::variant<Events::StockValueIsRisingEvent,
                     Events::StockValueIsFallingEvent,
                     Events::StockValueIsDoubledFromStartValueEvent,
                     Events::StockValueIsHalvedFromStartValueEvent,
                     Events::StockIsCrashedEvent>
    EventVariant;

typedef boost::signals2::signal<void(EventVariant)> AnalyserSignal;

class StockAnalyser
{

public:
  StockAnalyser();
  ~StockAnalyser();
  StockAnalyser(const Analyser::StockAnalyser &stockAnalyser);

  const void operator()(const std::vector<Stock> &stocks);

  template <typename T> const void attach(const T &cb)
  {
    // std::cout << "Analyser attach: " << analyserSignal_.get() << std::endl;
    analyserSignal_->connect(cb); // Calls copy contructor of StockRender, which
                                  // is okay because the pip ends
  }

private:
  // Analyser::AnalyserSignal analyserSignal_;
  boost::shared_ptr<Analyser::AnalyserSignal> analyserSignal_;
  std::vector<Stock>
               previousStockData_; // Must be inline if not declared in StockAnalyser.hpp
  void         notify(const EventVariant &eventVariant);
  const void   analyse(const std::vector<Stock> &stocks);
  EventVariant createEvent(const Events::Event event, const Stock &stock);

  void RaiseEventIfRising(const Stock &previousStock,
                          const Stock &updatedStock);
  void RaiseEventIfFalling(const Stock &previousStock,
                           const Stock &updatedStock);
  void RaiseEventIfDoubled(const Stock &updatedStock);
  void RaiseEventIfHalved(const Stock &updatedStock);
  void RaiseEventIfCrashed(const Stock &updatedStock);
  void RaiseEventIfNormal(const Stock &updatedStock);
};
} // namespace Analyser