#include "pages.h"

void draw_screen(Adafruit_ILI9341 &tft_display, const Screen & screen) {
    switch(screen) {
        case Screen::Splash:
            SplashScreen::draw_screen(tft_display);
            break;
        case Screen::CodePad:
            CodePadScreen::draw_screen(tft_display);
            break;
        case Screen::SelectMode:
            SelectModeScreen::draw_screen(tft_display);
            break;
        case Screen::Menu:
            break;
        default:
            break;
    }
    
}

void handle_touch(Adafruit_ILI9341 &tft_display, PubSubClient &client, const Screen & screen, const struct TouchPoint & touch_point) {
    switch(screen) {
        case Screen::Splash:
            // ignore
            break;
        case Screen::CodePad:
            CodePadScreen::handle_touch(tft_display, client, touch_point);
            break;
        case Screen::SelectMode:
            SelectModeScreen::handle_touch(tft_display, client, touch_point);
            break;
        case Screen::Menu:
            break;
        default:
            break;
    }
}
