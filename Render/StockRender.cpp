#include "Render/StockRender.hpp"

struct StockVisitor
{
  void operator()(Events::StockValueIsRisingEvent arg)
  {
    std::cout << "StockValueIsRisingEvent: " << std::endl;
  }
  void operator()(Events::StockValueIsFallingEvent arg)
  {
    std::cout << "StockValueIsFallingEvent: " << std::endl;
  }
  void operator()(Events::StockValueIsDoubledFromStartValueEvent arg)
  {
    std::cout << "StockValueIsDoubledFromStartValueEvent: "  << std::endl;
  }
  void operator()(Events::StockValueIsHalvedFromStartValueEvent arg)
  {
    std::cout << "StockValueIsHalvedFromStartValueEvent: " << std::endl;
  }
  void operator()(Events::StockIsCrashedEvent arg)
  {
    std::cout << "StockIsCrashedEvent: " << std::endl;
  }
  void operator()(Events::StockIsNormalEvent arg)
  {
    std::cout << "StockIsCrashedEvent: " << std::endl;
  }
};

Render::StockRender::StockRender() {}
Render::StockRender::~StockRender() {}

const void Render::StockRender::render(Analyser::EventVariant eventVariant)
{
  //std::cout << "Tissekone" << std::endl;
  std::visit(StockVisitor(), eventVariant);
}
