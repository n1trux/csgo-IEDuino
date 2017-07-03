
#include "ESP8266WiFi.h"
#include <Wire.h>
#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#include "fonts.h"

// Display Settings
const int I2C_DISPLAY_ADDRESS = 0x3c;
const int SDA_PIN = D2;
const int SDC_PIN = D3;

SSD1306  display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN);

OLEDDisplayUi ui ( &display );

int screenW = 128;
int screenH = 64;

// network settings
const char *ssid      = "your SSID here";
const char *password  = "your password here";

// bomb timer length
const int bombSeconds = 45;

void bombTimer() {
  Serial.println("Starting bombTimer()");
  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(DISPLAY_WIDTH/2, 0, "bomb timer started.");

  for ( float timer = bombSeconds*1.0; timer > 0; timer = timer - 0.1) {
    Serial.println("timer: "+String(timer)+" s");
    display.clear();
    display.setFont(ArialMT_Plain_10);
    display.drawString(DISPLAY_WIDTH/2, 10, "planted! time left:");
    display.setFont(Roboto_Black_28);
    display.drawString(DISPLAY_WIDTH/2, 43, String(timer)+" s");
    display.display();
    delay(100);
  }

}

void setup() {
  Serial.begin(115200);
  Serial.println();

  // set power supply for display as pin D4
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  ui.setTargetFPS(30);

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(TOP);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

  display.clear();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 20, "connecting to:");
  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 - 10, ssid);
  display.display();

  WiFi.begin ( ssid, password );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 10 );
  }

  display.drawString(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 + 5, "connected.");
}

void loop(/* arguments */) {
  Serial.println("In the Loop.");
  bombTimer();
}
