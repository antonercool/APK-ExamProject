#include "UIProvider.hpp"
#include <iostream>
#include "Stock.cpp"
#include "StockLoader.hpp"

using namespace Render;

int main(){

    std::cout << "Hello world" << std::endl;

    UIProvider cmdRender;

    cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld");

    Stock s;

}