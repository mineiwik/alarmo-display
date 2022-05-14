#include "pages/splash.h"

namespace SplashScreen {
    void draw_screen(Adafruit_ILI9341 &tft_display) {
    tft_display.fillRect(0, 0, 240, 320, ILI9341_WHITE);
    tft_display.drawRGBBitmap(20, 60, splash_icon, 200, 200);
    tft_display.setTextSize(1);
    tft_display.setTextColor(ILI9341_BLACK);
    const String app_version = APPLICATION_VERSION;
    int pixel_width = app_version.length() * 11;
    tft_display.setFont(&FreeMonoBold9pt7b);
    tft_display.setCursor((120 - (pixel_width/2)), 300);
    tft_display.println(app_version);
    tft_display.setFont(&FreeSansBold9pt7b);
    }
}
