#ifndef __H_SELECT_MODE__
#define __H_SELECT_MODE__

#include "Adafruit_ILI9341.h"
#include "PubSubClient.h"
#include "pages.h"
#include "communication.h"

namespace SelectModeScreen
{   
    #define TITLE_X                    SCREEN_X
    #define TITLE_Y                    SCREEN_Y
    #define TITLE_WIDTH                SCREEN_WIDTH
    #define TITLE_HEIGHT               80
    #define TITLE_CURSOR_POS_X         26
    #define TITLE_CURSOR_POS_Y         40 - TEXT_HEIGHT / 2

    #define NUM_ARM_MODES              4
    #define ARM_MODE_BTN_WIDTH         SCREEN_WIDTH
    #define ARM_MODE_BTN_HEIGHT        (SCREEN_HEIGHT - TITLE_HEIGHT) / NUM_ARM_MODES

    #define SELECT_MODE_H_LINE_X       SCREEN_X
    #define SELECT_MODE_H_LINE_Y       TITLE_HEIGHT
    #define SELECT_MODE_H_LINE_WIDTH   SCREEN_WIDTH
    #define SELECT_MODE_H_LINE_SPACING ARM_MODE_BTN_HEIGHT

    #define SELECT_MODE_CURSOR_OFFSET_X(txt_size) (ARM_MODE_BTN_WIDTH/2) - (txt_size * TEXT_WIDTH) / 2
    #define SELECT_MODE_CURSOR_OFFSET_Y(idx) TITLE_HEIGHT + (ARM_MODE_BTN_HEIGHT/2) - TEXT_HEIGHT / 2 + (ARM_MODE_BTN_HEIGHT * idx)

    enum ArmMode {
        ARM_HOME,
        ARM_AWAY,
        ARM_NIGHT,
        ARM_CUSTOM,
    };

    typedef struct {
        String text;
        int text_color;
        int button_color;
        enum ArmMode arm_mode;
    } arm_mode_button_t;

    void draw_screen(Adafruit_ILI9341 &tft_display);
    void draw_title(Adafruit_ILI9341 &tft_display);
    void handle_touch(Adafruit_ILI9341 &tft_display, PubSubClient &client, const struct TouchPoint &touch_point);
    int get_btn_index(int touch_point_y);

} // namespace SelectModeScreen

#endif
