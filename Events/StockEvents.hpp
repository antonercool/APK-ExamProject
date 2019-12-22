#pragma once
#include "Model/Stock.hpp"
#include <string>

namespace Events
{

enum class Event
{
  StockValueIsRisingEventEnum,
  StockValueIsFallingEventEnum,
  StockValueIsDoubledFromStartValueEventEnum,
  StockValueIsHalvedFromStartValueEventEnum,
  StockIsCrashedEventEnum
};

struct StockEventBase
{
  const Stock &stock;
};

struct StockValueIsRisingEvent : StockEventBase
{
};
struct StockValueIsFallingEvent : StockEventBase
{
};
struct StockValueIsDoubledFromStartValueEvent : StockEventBase
{
};
struct StockValueIsHalvedFromStartValueEvent : StockEventBase
{
};
struct StockIsCrashedEvent : StockEventBase
{
};

} // namespace Events
