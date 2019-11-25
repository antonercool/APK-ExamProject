#pragma once
#include "Events/StockEvents.hpp"
#include <boost/signals2.hpp>

namespace Analyser
{
typedef std::variant<
    Events::StockValueIsRisingEvent, Events::StockValueIsFallingEvent,
    Events::StockValueIsDoubledFromStartValueEvent,
    Events::StockValueIsHalvedFromStartValueEvent, Events::StockIsCrashedEvent>
    EventVariant;

class StockAnalyser
{
  typedef boost::signals2::signal<void(EventVariant)> AnalyserSignal;

public:
  StockAnalyser(/*StockSimulator &stockSimulator*/);
  ~StockAnalyser();
  StockAnalyser(const Analyser::StockAnalyser &stockAnalyser);

  const void operator()(const std::vector<Stock> &stocks);

  template <typename T> const void attach(const T &cb)
  {
    analyserSignal_.connect(cb);
  }
  // const void attach(const std::function<void(EventVariant)> &cb);

private:
  AnalyserSignal analyserSignal_;
  std::vector<Stock>
             previousStockData_; // Must be inline if not declared in StockAnalyser.hpp
  void       notify(const EventVariant &);
  const void analyse(const std::vector<Stock> &stocks);
};
} // namespace Analyser