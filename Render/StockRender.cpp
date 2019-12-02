#include "Render/StockRender.hpp"

struct StockVisitor
{
  void operator()(Events::StockValueIsRisingEvent arg)
  {
    std::cout << arg.stock.getName() << ": StockValueIsRisingEvent" << std::endl;
  }
  void operator()(Events::StockValueIsFallingEvent arg)
  {
    std::cout <<  arg.stock.getName() << ": StockValueIsFallingEvent" << std::endl;
  }
  void operator()(Events::StockValueIsDoubledFromStartValueEvent arg)
  {
    std::cout <<  arg.stock.getName() << ": StockValueIsDoubledFromStartValueEvent" << std::endl;
  }
  void operator()(Events::StockValueIsHalvedFromStartValueEvent arg)
  {
    std::cout <<  arg.stock.getName() << ": StockValueIsHalvedFromStartValueEvent" << std::endl;
  }
  void operator()(Events::StockIsCrashedEvent arg)
  {
    std::cout <<  arg.stock.getName() << ": StockIsCrashedEvent" << std::endl;
  }
  void operator()(Events::StockIsNormalEvent arg)
  {
    std::cout << arg.stock.getName() << ": StockIsNormalEvent" << std::endl;
  }
};

Render::StockRender::StockRender() {}
Render::StockRender::~StockRender() {}

const void Render::StockRender::callback(Analyser::EventVariant eventVariant)
{
  std::visit(StockVisitor(), eventVariant);
}
