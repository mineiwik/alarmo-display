#include "pages/menu.h"

namespace MenuScreen
{

    void draw_screen(Adafruit_ILI9341 &tft_display)
    {
        tft_display.fillRect(
            SCREEN_X, 
            SCREEN_Y, 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT, 
            ILI9341_BLACK
        );
        
        tft_display.setFont(0);
    }
    
} // namespace MenuScreen
