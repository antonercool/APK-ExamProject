#pragma once
#include "Analyser/StockAnalyser.hpp"
#include "Render/UIProvider.hpp"
#include "Model/Stock.hpp"

namespace Render
{

   struct UIInformation
    {
        int x;
        int y;
        bool isRising;
        bool isDouble;
        bool isHalfed;
        bool isCrashed;
    };

class StockRender
{

public:
  StockRender(Render::UIProvider* provider);
  ~StockRender();

  void operator()(Events::StockValueIsRisingEvent& arg);
  void operator()(Events::StockValueIsFallingEvent& arg);
  void operator()(Events::StockValueIsDoubledFromStartValueEvent& arg);
  void operator()(Events::StockValueIsHalvedFromStartValueEvent& arg);
  void operator()(Events::StockIsCrashedEvent& arg);
 
  const void callback(Analyser::EventVariant eventVariant);

private:
  Render::UIProvider* uiProvider_;
   std::map<const std::string, Render::UIInformation> stocksMap_;
   void registerRenderInfo(const Stock & stock);
   void printInfo(const Render::UIInformation& info, const Stock & stock);
  

  
};
} // namespace Render