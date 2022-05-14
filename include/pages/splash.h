#ifndef __H_SPLASH__
#define __H_SPLASH__

#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "Adafruit_ILI9341.h"
#include "splash_graphic.h"
#include "constants.h"

namespace SplashScreen {
    void draw_screen(Adafruit_ILI9341 &tft_display);
}

#endif
