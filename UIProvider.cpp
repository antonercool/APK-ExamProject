#include <iostream>
#include "UIProvider.hpp"

using namespace Render;

UIProvider::UIProvider(){

}
 
UIProvider::~UIProvider(){
    
}


// Colors
void UIProvider::setColor(Color newColor){
    this->_currentColor = newColor;
}

void UIProvider::outPutWithColor(Color color, std::string outPutString){
    std::cout << "\033[" << color << outPutString;
}

void UIProvider::resetToDefaultColor(){
    this->_currentColor = Color::DEFAULT;
}

// Initialize base CMD GUI
void UIProvider::initUI(){

}   

 // Fully Clear CMD GUI
void UIProvider::clearUI(){

} 

// Edit some chars on UI for performance
void UIProvider::updateUI(){

}

// Fully render UI (Clear and Render)
void UIProvider::renderUI(){

} 



