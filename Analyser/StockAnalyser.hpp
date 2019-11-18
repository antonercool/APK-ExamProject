#pragma once
#include "Events/StockEvents.hpp"
#include "Simulator/StockSimulator.hpp"
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
  StockAnalyser();
  ~StockAnalyser();

  const void analyse(std::vector<Stock> stocks);

  void attach(const std::function<void(EventVariant)> &cb);

private:
  AnalyserSignal analyserSignal_;
  std::vector<Stock>
      previousStockData_; // Must be inline if not declared in StockAnalyser.hpp
  void notify(const EventVariant&);

};
} // namespace Analyser