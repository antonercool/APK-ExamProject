#include <iostream>
#include "Render/UIProvider.hpp"

using namespace Render;

UIProvider::UIProvider(){
   
}
 
UIProvider::~UIProvider(){
    
}

// Initialize base CMD GUI
void UIProvider::initUI(){
    // Remove blinking curser
    removeCurser();
    // clear cmd UI
    clearUI();
}   

 // Fully Clear CMD GUI
void UIProvider::clearUI(){
    std::system("clear");
} 

// Edit some chars on UI for performance (parcial)
void UIProvider::updateUI(unsigned int y, unsigned int x, std::string toRender){
    printf("\033[%d;%dH%s\n", y, x, toRender.c_str());
}

void UIProvider::removeCurser(){
    std::cout << "\e[?25l" << std::endl;
}



