/*
 * HomeDisplay - select_mode.cpp
 * Description: implements `SelectMode` screen
 * Author: mineiwik <dev@mineiwik.dev>
 * License: MIT
 */

/*
 *     <--  240  -->
 * ^   ############# ^
 * 80  #   MODE    # |
 * v ^ ############# |
 *  60 # Arm Home  #
 * ^ v ############# 
 * 60  # Arm Away  # 320
 * v ^ ############# 
 *  60 # Arm Night #
 * ^ v ############# |
 * 60  # Arm Custom# |
 * v   ############# v
 */

#include "pages/select_mode.h"

namespace SelectModeScreen
{
    const arm_mode_button_t arm_mode_buttons[NUM_ARM_MODES] = {
        {
            .text = MODE_HOME_TEXT,
            .text_color = ILI9341_WHITE,
            .button_color = ILI9341_DARKGREEN,
            .arm_mode = ArmMode::ARM_HOME,
        },
        {
            .text = MODE_AWAY_TEXT,
            .text_color = ILI9341_WHITE,
            .button_color = ILI9341_BLUE,
            .arm_mode = ArmMode::ARM_AWAY,
        },
        {
            .text = MODE_NIGHT_TEXT,
            .text_color = ILI9341_WHITE,
            .button_color = ILI9341_DARKGREY,
            .arm_mode = ArmMode::ARM_NIGHT,
        },
        {
            .text = MODE_CUSTOM_TEXT,
            .text_color = ILI9341_WHITE,
            .button_color = ILI9341_DARKGREY,
            .arm_mode = ArmMode::ARM_CUSTOM,
        }
    };

    void draw_title(Adafruit_ILI9341 &tft_display)
    {
        tft_display.fillRect(
            TITLE_X, 
            TITLE_Y, 
            TITLE_WIDTH, 
            TITLE_HEIGHT, 
            ILI9341_CYAN
        );
               
        tft_display.setCursor(TITLE_CURSOR_POS_X, TITLE_CURSOR_POS_Y);
        tft_display.setTextSize(TEXT_SIZE);
        tft_display.setTextColor(ILI9341_BLACK);
        tft_display.println(MODE_TEXT);
    }

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

        draw_title(tft_display);

        // Drawing the arm modes
        for (int i = 0; i < NUM_ARM_MODES; i++) {
            arm_mode_button_t arm_mode_btn = arm_mode_buttons[i];
            int text_size = arm_mode_btn.text.length();
            tft_display.fillRect(
                0, 
                TITLE_HEIGHT + i * ARM_MODE_BTN_HEIGHT, 
                ARM_MODE_BTN_WIDTH, 
                ARM_MODE_BTN_HEIGHT, 
                arm_mode_btn.button_color
            );
            tft_display.setCursor(
                SELECT_MODE_CURSOR_OFFSET_X(text_size),
                SELECT_MODE_CURSOR_OFFSET_Y(i)
            );
            tft_display.setTextSize(TEXT_SIZE);
            tft_display.setTextColor(arm_mode_btn.text_color);
            tft_display.println(arm_mode_btn.text);
        }

        // Drawing horicontal lines
        for (int h = SELECT_MODE_H_LINE_Y; h <= SCREEN_HEIGHT; h += SELECT_MODE_H_LINE_SPACING) {
            tft_display.drawFastHLine(
                SELECT_MODE_H_LINE_X, 
                h, 
                SELECT_MODE_H_LINE_WIDTH, 
                ILI9341_WHITE
            );
        }
    }

    /**
     * Handles touch event
     * 
     * @param tft_display reference to the tft display handler
     * @param client reference to the PubSubClient for MQTT communication
     * @param touch_point coordinates of touch point
     * 
     */
    void handle_touch(Adafruit_ILI9341 &tft_display, PubSubClient &client, const struct TouchPoint &touch_point) {
        // Discard touch points outside button range
        if (touch_point.y < TITLE_HEIGHT)
            return;
        
        int btn_idx = get_btn_index(touch_point.y);
        if (btn_idx < 0) return;

        arm_mode_button_t arm_mode_btn = arm_mode_buttons[btn_idx];

        String payload = "";

        switch (arm_mode_btn.arm_mode) {
            case ArmMode::ARM_HOME:
                payload = "{\"command\":\"ARM_HOME\"}";
                client.publish(ALARMO_COMMAND_TOPIC, payload.c_str());
                break;
            case ArmMode::ARM_AWAY:
                payload = "{\"command\":\"ARM_AWAY\"}";
                client.publish(ALARMO_COMMAND_TOPIC, payload.c_str());
                break;
            case ArmMode::ARM_NIGHT:
                payload = "{\"command\":\"ARM_NIGHT\"}";
                client.publish(ALARMO_COMMAND_TOPIC, payload.c_str());
                break;
            case ArmMode::ARM_CUSTOM:
                payload = "{\"command\":\"ARM_CUSTOM_BYPASS\"}";
                client.publish(ALARMO_COMMAND_TOPIC, payload.c_str());
                break;
        }
    }

    int get_btn_index(int touch_point_y) {
        // Subtract offset
        touch_point_y -= TITLE_HEIGHT;

        // Check for dead zone
        int row_offset = touch_point_y % (ARM_MODE_BTN_HEIGHT);
        if (row_offset <= TOUCH_PADDING || row_offset >= (ARM_MODE_BTN_HEIGHT) - TOUCH_PADDING)
            return -1;

        return touch_point_y / (ARM_MODE_BTN_HEIGHT);
    }
}
