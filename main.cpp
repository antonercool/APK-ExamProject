#include "UIProvider.hpp"
#include <iostream>
#include "Stock.hpp"

using namespace Render;

int main(){


    UIProvider cmdRender;

    cmdRender.setColor(Render::Color::BLUE);
    cmdRender.print("This should be blue\n");


    cmdRender.setColor(Render::Color::RED);
    cmdRender.print("This should be red\n");


    cmdRender.setColor(Render::Color::GREEN);
    cmdRender.print("This should be Green\n");
    
   
    cmdRender.outPutWithColor(Render::Color::GREEN, "HelloWorld\n");
    cmdRender.resetToDefaultColor();
    cmdRender.print("This should have default color\n");
    
    Stock s;

    getchar();

}