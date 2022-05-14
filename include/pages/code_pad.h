#ifndef __H_CODE_PAD__
#define __H_CODE_PAD__

#include "Adafruit_ILI9341.h"
#include "PubSubClient.h"
#include "pages.h"
#include "communication.h"

namespace CodePadScreen
{   
    #define RESULT_X                SCREEN_X
    #define RESULT_Y                SCREEN_Y
    #define RESULT_WIDTH            SCREEN_WIDTH
    #define RESULT_HEIGHT           80
    #define RESULT_CURSOR_POS_X     26
    #define RESULT_CURSOR_POS_Y     40 - TEXT_HEIGHT / 2

    #define PAD_COLS                3
    #define PAD_ROWS                4
    #define PAD_KEY_WIDTH           SCREEN_WIDTH / PAD_COLS
    #define PAD_KEY_HEIGHT          (SCREEN_HEIGHT - RESULT_HEIGHT) / PAD_ROWS
    #define HALF_KEY_WIDTH          PAD_KEY_WIDTH / 2
    #define HALF_KEY_HEIGHT         PAD_KEY_HEIGHT / 2

    #define CODE_PAD_H_LINE_X       SCREEN_X
    #define CODE_PAD_H_LINE_Y       RESULT_HEIGHT
    #define CODE_PAD_H_LINE_WIDTH   SCREEN_WIDTH
    #define CODE_PAD_H_LINE_SPACING PAD_KEY_HEIGHT

    #define CODE_PAD_V_LINE_X       SCREEN_WIDTH / PAD_COLS
    #define CODE_PAD_V_LINE_Y       RESULT_HEIGHT
    #define CODE_PAD_V_LINE_HEIGHT  SCREEN_HEIGHT - RESULT_HEIGHT
    #define CODE_PAD_V_LINE_SPACING PAD_KEY_WIDTH

    #define CODE_PAD_CURSOR_OFFSET_X(txt_size, idx) HALF_KEY_WIDTH - (txt_size * TEXT_WIDTH) / 2 + (PAD_KEY_WIDTH * idx)
    #define CODE_PAD_CURSOR_OFFSET_Y(idx) RESULT_HEIGHT + HALF_KEY_HEIGHT - TEXT_HEIGHT / 2 + (PAD_KEY_HEIGHT * idx)

    enum KeyType {
        Digit,
        Clear,
        Enter,
    };

    struct PadKey {
        String text;
        int color;
        KeyType key_type;
        int digit;
    };

    void draw_screen(Adafruit_ILI9341 &tft_display);
    void draw_result(Adafruit_ILI9341 &tft_display, int color);
    void handle_touch(Adafruit_ILI9341 &tft_display, PubSubClient &client, const struct TouchPoint &touch_point);
    int get_row_index(int touch_point_y);
    int get_col_index(int touch_point_x);

} // namespace CodePad

#endif
