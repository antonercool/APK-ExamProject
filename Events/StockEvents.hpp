#pragma once
#include <string>
#include "Model/Stock.hpp"

namespace Events
{

struct StockValueIsRisingEvent
{
  const Stock& stock;
};

struct StockValueIsFallingEvent
{
 const Stock& stock; 
};

struct StockValueIsDoubledFromStartValueEvent
{
  const Stock& stock;
};

struct StockValueIsHalvedFromStartValueEvent
{
  const Stock& stock;
};

struct StockIsCrashedEvent
{
  const Stock& stock;
};

} // namespace Events
