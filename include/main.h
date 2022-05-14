#include <Arduino.h>
#include <ArduinoOTA.h>
#include "ESP8266WiFi.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "PubSubClient.h"
#include "pages.h"
#include "types.h"
#include "communication.h"

#define TFT_CS D1
#define TFT_DC D2
#define TFT_LED D8

#define TOUCH_CS D3
#define TOUCH_IRQ D4

#define MINPRESSURE 10
#define TS_MINX 370
#define TS_MINY 470
#define TS_MAXX 3700
#define TS_MAXY 3600

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#define DISPLAY_STANDBY_TIMEOUT_SECONDS 30
#define DISPLAY_WAKE_UP_TIMEOUT_SECONDS 1

enum DisplayStatus {
    DISPLAY_STANDBY,
    DISPLAY_WAKE_UP,
    DISPLAY_ON,
};

bool is_new_touch();
