#include "UIProvider.hpp"
#include <iostream>
#include "Stock.cpp"
#include "StockLoader.hpp"
#include <boost/array.hpp>
using namespace Render;

int main(){

    std::cout << "Hello world" << std::endl;

    UIProvider cmdRender;

    //cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld");

    StockLoader sl;

    std::vector<Stock>* stocks = sl.loadStocks("./stockDb");

    for(Stock stock: *stocks){
        std::cout << stock << std::endl;
    }
}