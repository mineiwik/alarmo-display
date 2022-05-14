#ifndef __H_PAGES__
#define __H_PAGES__

#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include "PubSubClient.h"
#include "types.h"
#include "pages/splash.h"
#include "pages/code_pad.h"
#include "pages/select_mode.h"
#include "pages/menu.h"

#define SCREEN_X 0
#define SCREEN_WIDTH 240
#define SCREEN_Y 0
#define SCREEN_HEIGHT 320

#define TEXT_SIZE           3
#define TEXT_WIDTH          18
#define TEXT_HEIGHT         24

#define TOUCH_PADDING 0

#define BEEPER D0

enum Screen {
    Splash,
    CodePad,
    Menu,
    SelectMode
};

void draw_screen(Adafruit_ILI9341 &tft_display, const Screen & screen);
void handle_touch(Adafruit_ILI9341 &tft_display, PubSubClient &client, const Screen & screen, const struct TouchPoint & touch_point);

#endif
