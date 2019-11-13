#include "StockMarketRender/UIProvider.hpp"
#include <iostream>

using namespace Render;

int main(){

    std::cout << "Hello world" << std::endl;

    UIProvider cmdRender;

    cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld");

}