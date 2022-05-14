/*
 * HomeDisplay - code_pad.cpp
 * Description: implements `CodePad` screen
 * Author: mineiwik <dev@mineiwik.dev>
 * License: MIT
 */

/*
 *     <--  240  -->
 * ^   ############# ^
 * 80  #  RESULT   # |
 * v ^ ############# |
 *  60 # 7 # 8 # 9 #
 * ^ v ############# 
 * 60  # 4 # 5 # 6 # 320
 * v ^ ############# 
 *  60 # 1 # 2 # 3 #
 * ^ v ############# |
 * 60  # C # 0 # OK# |
 * v   ############# v
 *     <80 >   <80 >
 *         <80 >
 */

#include "pages/code_pad.h"

namespace CodePadScreen
{
    const PadKey pad_keys[PAD_ROWS][PAD_COLS] = {
        {
            {"7", ILI9341_BLACK, KeyType::Digit, 7}, 
            {"8", ILI9341_BLACK, KeyType::Digit, 8}, 
            {"9", ILI9341_BLACK, KeyType::Digit, 9}
        },
        {
            {"4", ILI9341_BLACK, KeyType::Digit, 4}, 
            {"5", ILI9341_BLACK, KeyType::Digit, 5}, 
            {"6", ILI9341_BLACK, KeyType::Digit, 6}
        },
        {
            {"1", ILI9341_BLACK, KeyType::Digit, 1}, 
            {"2", ILI9341_BLACK, KeyType::Digit, 2}, 
            {"3", ILI9341_BLACK, KeyType::Digit, 3}
        },
        {
            {"C", ILI9341_RED, KeyType::Clear, -1}, 
            {"0", ILI9341_BLACK, KeyType::Digit, 0}, 
            {"OK", ILI9341_GREEN, KeyType::Enter, -1}
        }
    };

    String digits = "";
    String text = "";

    void draw_result(Adafruit_ILI9341 &tft_display, int color)
    {
        tft_display.fillRect(
            RESULT_X, 
            RESULT_Y, 
            RESULT_WIDTH, 
            RESULT_HEIGHT, 
            color
        );
        
        if (text.isEmpty())
            return;
        
        tft_display.setCursor(RESULT_CURSOR_POS_X, RESULT_CURSOR_POS_Y);
        tft_display.setTextSize(TEXT_SIZE);
        tft_display.setTextColor(ILI9341_BLACK);
        tft_display.println(text);
    }

    void draw_screen(Adafruit_ILI9341 &tft_display)
    {
        digits = "";
        text = KEYPAD_ENTER_PIN_TEXT;

        tft_display.fillRect(
            SCREEN_X, 
            SCREEN_Y, 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT, 
            ILI9341_BLACK
        );
        
        tft_display.setFont(0);

        draw_result(tft_display, ILI9341_CYAN);

        // Drawing the keys
        for (int j = 0; j < PAD_ROWS; j++) {
            for (int i = 0; i < PAD_COLS; i++) {
                PadKey pad_key = pad_keys[j][i];
                int text_size = pad_key.text.length();
                tft_display.fillRect(
                    i * PAD_KEY_WIDTH, 
                    RESULT_HEIGHT + j * PAD_KEY_HEIGHT, 
                    PAD_KEY_WIDTH, 
                    PAD_KEY_HEIGHT, 
                    pad_key.color
                );
                tft_display.setCursor(
                    CODE_PAD_CURSOR_OFFSET_X(text_size, i),
                    CODE_PAD_CURSOR_OFFSET_Y(j)
                );
                tft_display.setTextSize(TEXT_SIZE);
                tft_display.setTextColor(ILI9341_WHITE);
                tft_display.println(pad_key.text);
            }
        }

        // Drawing horicontal lines
        for (int h = CODE_PAD_H_LINE_Y; h <= SCREEN_HEIGHT; h += CODE_PAD_H_LINE_SPACING)
            tft_display.drawFastHLine(
                CODE_PAD_H_LINE_X, 
                h, 
                CODE_PAD_H_LINE_WIDTH, 
                ILI9341_WHITE
            );

        // Drawing vertical lines
        for (int v = CODE_PAD_V_LINE_X; v <= SCREEN_WIDTH; v += CODE_PAD_V_LINE_SPACING)
            tft_display.drawFastVLine(
                v, 
                CODE_PAD_V_LINE_Y, 
                CODE_PAD_V_LINE_HEIGHT, 
                ILI9341_WHITE
            );
    }

    /**
     * Handles touch event on keypad screen.
     * 
     * @param tft_display reference to the tft display handler
     * @param touch_point coordinates of touch point
     * 
     */
    void handle_touch(Adafruit_ILI9341 &tft_display, PubSubClient &client, const struct TouchPoint &touch_point) {
        // Discard touch points outside keypad
        if (touch_point.y < RESULT_HEIGHT)
            return;
        
        int col = get_col_index(touch_point.x);
        int row = get_row_index(touch_point.y);
        if (col < 0) return;
        if (row < 0) return;

        PadKey pad_key = pad_keys[row][col];

        switch (pad_key.key_type) {
            case KeyType::Digit:
                digits += pad_key.digit;
                text = "";
                for (unsigned int i = 0; i < digits.length(); i++) {
                    text += "*";
                }
                break;
            case KeyType::Clear:
                digits = "";
                text = KEYPAD_ENTER_PIN_TEXT;
                break;
            case KeyType::Enter:
                String payload = "{\"command\":\"disarm\",\"code\":\"" + digits + "\"}";
                client.publish(ALARMO_COMMAND_TOPIC, payload.c_str());
                digits = "";
                text = KEYPAD_SENT_TEXT;
                break;
        }

        draw_result(tft_display, ILI9341_CYAN);
    }

    int get_row_index(int touch_point_y) {
        // Subtract offset
        touch_point_y -= RESULT_HEIGHT;

        // Check for dead zone
        int row_offset = touch_point_y % PAD_KEY_HEIGHT;
        if (row_offset <= TOUCH_PADDING || row_offset >= PAD_KEY_HEIGHT - TOUCH_PADDING)
            return -1;

        return touch_point_y / (PAD_KEY_HEIGHT);
    }

    int get_col_index(int touch_point_x) {
        // Check for dead zone
        int col_offset = touch_point_x % PAD_KEY_WIDTH;
        if (col_offset <= TOUCH_PADDING || col_offset >= PAD_KEY_WIDTH - TOUCH_PADDING)
            return -1;

        return touch_point_x / (PAD_KEY_WIDTH);
    }
}
