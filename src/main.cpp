#include "main.h"
#include "pages.h"

WiFiClient espClient;
PubSubClient client(espClient);

Adafruit_ILI9341 tft_display = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen touch(TOUCH_CS);

Screen current_screen = Screen::Splash;

struct TouchPoint touch_point;
long Num1, Num2, Number;
char action;
boolean result = false;
TS_Point p;

enum DisplayStatus display_status = DISPLAY_STANDBY;

long unsigned int wake_up_cnt = 0;
long unsigned int time_cnt = 0;

void callback(char *topic, byte *payload, unsigned int length)
{
  // When new message arrived
  if (strcmp(topic, ALARMO_STATE_TOPIC) == 0) {
    if (!strncmp((char *)payload, "disarmed", length)) {
          // DISARMED
          current_screen = Screen::SelectMode;
          draw_screen(tft_display, current_screen);
      } else {
          // ARMED
          current_screen = Screen::CodePad;
          draw_screen(tft_display, current_screen);
      }
  }
}

void reconnect()
{
  while (!client.connected())
  {
    String clientId = "ha-panel-1";
    if (client.connect(clientId.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
    {
      client.subscribe(ALARMO_STATE_TOPIC);
    }
    else
    {
      delay(5000);
    }
  }
}

void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  randomSeed(micros());
}

void setup()
{
  current_screen = Screen::Splash;

  pinMode(TFT_LED, OUTPUT);

  tft_display.begin();
  touch.begin();
  tft_display.fillScreen(ILI9341_BLACK);

  draw_screen(tft_display, current_screen);

  digitalWrite(TFT_LED, HIGH);

  /*
   * Connect to WIFI and MQTT server
   */
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  delay(1500);

  ArduinoOTA.begin();

  time_cnt = millis()/1000 + DISPLAY_STANDBY_TIMEOUT_SECONDS;
  display_status = DISPLAY_ON;
}

void loop()
{
  if (millis()/1000 > time_cnt) {
    // Turn display off
    display_status = DISPLAY_STANDBY;
    digitalWrite(TFT_LED, LOW);
    wake_up_cnt = millis()/1000 + DISPLAY_WAKE_UP_TIMEOUT_SECONDS;
  } else if (millis()/1000 < wake_up_cnt) {
    display_status = DISPLAY_WAKE_UP;
    digitalWrite(TFT_LED, HIGH);
  } else {
    // Turn display on
    display_status = DISPLAY_ON;
    digitalWrite(TFT_LED, HIGH);
  }
  ArduinoOTA.handle();

  if (!client.connected())
  {
    reconnect();
  }

  client.loop();

  // if new touch is detected
  if (is_new_touch() && display_status == DISPLAY_ON)
  {
    // handle touch event according to current state
    handle_touch(tft_display, client, current_screen, touch_point);
  }
  delay(100);
}

bool is_new_touch()
{
  p = touch.getPoint();
  delay(1);
  touch_point.x = map(p.y, TS_MINX, TS_MAXX, 0, SCREEN_WIDTH-1);
  touch_point.y = map(p.x, TS_MINY, TS_MAXY, SCREEN_HEIGHT-1, 0);
  if (p.z > MINPRESSURE) {
    time_cnt = millis()/1000 + DISPLAY_STANDBY_TIMEOUT_SECONDS;
    return true;
  }
  return false;
}
