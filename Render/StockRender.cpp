#include "Render/StockRender.hpp"

void Render::StockRender::printInfo(const Render::UIInformation& info, const Stock & stock){

  std::string clearLine("                                                                                                              ");
  uiProvider_->updateUI(info.y,0, clearLine);
  std::string discription = "Stock name : " + stock.getName() + ", current price : " + std::to_string(stock.getValue());
  uiProvider_->updateUI(info.y, 0, discription);

  if(info.isRising){
      std::string rishing = uiProvider_->generateStringWithColor("UP", Color::GREEN);
      uiProvider_->updateUI(info.y, 60,rishing);
  }
  else{
     std::string falling = uiProvider_->generateStringWithColor("DOWN", Color::RED);
      uiProvider_->updateUI(info.y, 60,falling);
  }

  if (info.isDouble)
  {
    std::string doubleUp = uiProvider_->generateStringWithColor("double", Color::BLUE);
    uiProvider_->updateUI(info.y, 80,doubleUp);
  }
  
  if (info.isHalfed)
  {
    std::string halved = uiProvider_->generateStringWithColor("halved", Color::BLUE);
    uiProvider_->updateUI(info.y, 80,halved);
  }

  if (info.isCrashed)
  {
     std::string crashed = uiProvider_->generateStringWithColor("CRASHED", Color::RED);
     uiProvider_->updateUI(info.y, 100,crashed);
  }

}

// Registor event info for stock, if it is now registored allreaddy
void Render::StockRender::registorRenderInfo(const Stock & stock){
  auto result = stocksMap_.find(stock.getName());
  // if not found
  if (result == stocksMap_.end())
  {
    // registor coords and defualt event info for stock
    unsigned yIndexToCreate = (stocksMap_.size() == 0) ? 0 : (int)stocksMap_.size() + 2;
    Render::UIInformation info{0, yIndexToCreate};
    // [name] creates if it is not there
    stocksMap_[stock.getName()] = info;
  }
 
}

void Render::StockRender::operator()(Events::StockValueIsRisingEvent arg)
{
  registorRenderInfo(arg.stock);
  stocksMap_[arg.stock.getName()].isRising = true;
  printInfo(stocksMap_[arg.stock.getName()], arg.stock);

}
void Render::StockRender::operator()(Events::StockValueIsFallingEvent arg)
{
  registorRenderInfo(arg.stock);
  stocksMap_[arg.stock.getName()].isRising = false;
  printInfo(stocksMap_[arg.stock.getName()], arg.stock);
}

void Render::StockRender::operator()(Events::StockValueIsDoubledFromStartValueEvent arg)
{
  registorRenderInfo(arg.stock);
  stocksMap_[arg.stock.getName()].isDouble = true;
  printInfo(stocksMap_[arg.stock.getName()], arg.stock);
}
void Render::StockRender::operator()(Events::StockValueIsHalvedFromStartValueEvent arg)
{
  registorRenderInfo(arg.stock);
  stocksMap_[arg.stock.getName()].isHalfed = true;
  printInfo(stocksMap_[arg.stock.getName()], arg.stock);
}

void Render::StockRender::operator()(Events::StockIsCrashedEvent arg)
{
  registorRenderInfo(arg.stock);
  stocksMap_[arg.stock.getName()].isCrashed = true;
  printInfo(stocksMap_[arg.stock.getName()], arg.stock);;
}

Render::StockRender::StockRender(Render::UIProvider *provider) : uiProvider_(provider)
{
  uiProvider_->initUI();
}



Render::StockRender::~StockRender() {}

const void Render::StockRender::render(Analyser::EventVariant eventVariant)
{
  std::visit(*this, eventVariant);
}
