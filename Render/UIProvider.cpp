#include <iostream>
#include "Render/UIProvider.hpp"

using namespace Render;

UIProvider::UIProvider(unsigned int height, unsigned int width){
    this->height_ = height;
    this->width_  = width;
}
 
UIProvider::~UIProvider(){
    
}

// Colors
void UIProvider::setColor(Color newColor){
    this->_currentColor = newColor;
}

void UIProvider::outPutWithColor(Color color, std::string outPutString){
    std::cout << "\033[" << color <<"m" << outPutString << "\033[0m";
}

 std::string UIProvider::generateStringWithColor(std::string toCreate, Color color){
     std::string stringToBuild = "\033[" + std::to_string((int)color) + "m" + toCreate + "\033[0m";
     return stringToBuild;
 }

void UIProvider::resetToDefaultColor(){
    this->_currentColor = Color::DEFAULT;
}

void UIProvider::print(std::string outPutString){
    std::cout << "\033[" << this->_currentColor <<"m" << outPutString << "\033[0m";
    
}

// Initialize base CMD GUI
void UIProvider::initUI(){
    // Remove blinking curser
   //inizializeHeightAndWidth(height_, width_);
    removeCurser();
    clearUI();

    //for (size_t i = 0; i < count; i++)
    //{
    //    /* code */
    //}
    

}   

 // Fully Clear CMD GUI
void UIProvider::clearUI(){
    std::system("clear");
} 

// Edit some chars on UI for performance
void UIProvider::updateUI(unsigned int y, unsigned int x, std::string toRender){
    printf("\033[%d;%dH%s\n", y, x, toRender.c_str());
}

// Fully render UI (Clear and Render)
void UIProvider::renderUI(){

} 

void UIProvider::removeCurser(){
    std::cout << "\e[?25l" << std::endl;
}

void UIProvider::inizializeHeightAndWidth(unsigned int height, unsigned int width){
    //std::cout << "\e[8;"<<height<< ";" << width<< "t" << std::endl;;
    std::cout << "\e[8;500;500t";
}


