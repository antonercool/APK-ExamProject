#pragma once
#include "Model/Stock.hpp"
#include <string>

namespace Events
{

enum Event
{
  StockValueIsRisingEventEnum,
  StockValueIsFallingEventEnum,
  StockValueIsDoubledFromStartValueEventEnum,
  StockValueIsHalvedFromStartValueEventEnum,
  StockIsCrashedEventEnum,
  StockIsNormalEventEnum
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
struct StockIsNormalEvent : StockEventBase
{
};

} // namespace Events
