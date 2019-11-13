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
        Color _currentColor = DEFAULT;
       
    public:
        UIProvider();
        ~UIProvider();

        // Colors
        void setColor(Color);
        void outPutWithColor(Color, std::string);
        void resetToDefaultColor();
        void print(std::string);

        void initUI();   // Initialize base CMD GUI
        void clearUI();  // Fully Clear CMD GUI
        void updateUI(); // Edit some chars on UI for performance
        void renderUI(); // Fully render UI (Clear and Render)
    };
} 
