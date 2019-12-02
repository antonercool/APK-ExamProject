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
  StockIsCrashedEventEnum
};

struct StockValueIsRisingEvent
{
  const Stock &stock;
};

struct StockValueIsFallingEvent
{
  const Stock &stock;
};

struct StockValueIsDoubledFromStartValueEvent
{
  const Stock &stock;
};

struct StockValueIsHalvedFromStartValueEvent
{
  const Stock &stock;
};

struct StockIsCrashedEvent
{
  const Stock &stock;
};


} // namespace Events
