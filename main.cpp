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

    Stock s;

    StockLoader sl;

    sl.loadStocks("");

    //boost::array<int, 4> ar = {1,2,3,4};

}