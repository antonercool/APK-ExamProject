#pragma once
#include <string>


namespace Render{    
    
   enum Color {
        RED      = 31,
        GREEN    = 32,
        BLUE     = 34,
        DEFAULT  = 39
    };

    class UIProvider{
    private:
        /* data */
        unsigned int height_;
        unsigned int width_;
        Color _currentColor = DEFAULT;
        void removeCurser(); // remove blinking curser
        void inizializeHeightAndWidth(unsigned int height, unsigned int width);
        

    
    public:
        UIProvider(unsigned int height, unsigned int width);
        ~UIProvider();

        // Colors
        void setColor(Color);
        void outPutWithColor(Color, std::string);
        void resetToDefaultColor();
        void print(std::string);
        std::string generateStringWithColor(std::string, Color);

        void initUI();   // Initialize base CMD GUI
        void clearUI();  // Fully Clear CMD GUI
        void updateUI(unsigned int x, unsigned int y, std::string toRender); // Edit some chars on UI for performance
        void renderUI(); // Fully render UI (Clear and Render)
       
    };
} 
