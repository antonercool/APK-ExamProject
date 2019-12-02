#pragma once
#include "Analyser/StockAnalyser.hpp"

namespace Render
{

class StockRender
{

public:
  StockRender();
  ~StockRender();

  const void callback(Analyser::EventVariant eventVariant);

private:
};
} // namespace Render