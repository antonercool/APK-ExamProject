#include "UIProvider.hpp"
#include <iostream>
#include "Stock.cpp"
#include "StockLoader.hpp"
#include <boost/array.hpp>
using namespace Render;

int main(){


    UIProvider cmdRender;


    StockLoader sl;

    std::vector<Stock>* stocks = sl.loadStocks("./stockDb");

    for(Stock stock: *stocks){
        std::cout << stock << std::endl;
    }

    cmdRender.setColor(Render::Color::BLUE);
    cmdRender.print("This should be blue\n");


    cmdRender.setColor(Render::Color::RED);
    cmdRender.print("This should be red\n");


    cmdRender.setColor(Render::Color::GREEN);
    cmdRender.print("This should be Green\n");
    
   
    cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld\n");
    cmdRender.resetToDefaultColor();
    cmdRender.print("This should have default color\n");
    
    getchar();


}