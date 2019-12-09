#pragma once
#include <string>


namespace Render{    
    
   enum Color {
        RED         = 31,
        GREEN       = 32,
        YELLOW      = 33,
        BLUE        = 34,
        PURPLE      = 35,
        CYAN        = 36,
        LIGHTGREY   = 37,
        DEFAULT     = 39
    };

    class UIProvider{
    private:
        void removeCurser(); // remove blinking curser
        
    public:
        UIProvider(unsigned int height, unsigned int width);
        ~UIProvider();

        std::string generateStringWithColor(std::string, Color);
        void initUI();   // Initialize base CMD GUI
        void clearUI();  // Fully Clear CMD GUI
        void updateUI(unsigned int x, unsigned int y, std::string toRender); // Edit some chars on UI for performance
       
    };
} 
