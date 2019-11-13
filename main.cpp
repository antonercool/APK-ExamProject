#include "UIProvider.hpp"
#include <iostream>
#include "Stock.hpp"

using namespace Render;

int main(){

    std::cout << "Hello world" << std::endl;

    UIProvider cmdRender;

    cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld");

    Stock s;

}