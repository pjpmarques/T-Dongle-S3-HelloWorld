
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <OneButton.h>
#include <FastLED.h>
#include "pin_config.h"

TFT_eSPI tft;
CRGB leds;
OneButton button(BTN_PIN, true);

// ------------------------------------------------------------------------------------

void button_task(void *param) {
  while (1) {
    button.tick();
    delay(50);
  }
}

void button_pressed() {
  FastLED.showColor(CRGB::Yellow);
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, TFT_YELLOW);
  tft.setTextColor(TFT_BLACK, TFT_YELLOW);
  tft.drawString("YELLOW", TFT_HEIGHT/2, TFT_WIDTH/2, 4);
  Serial.println("Yellow");
}

// ------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setTextFont(7);
  tft.setTextDatum(CC_DATUM);
  tft.fillRect(0, 0, TFT_WIDTH, TFT_HEIGHT, TFT_BLACK);
  tft.setRotation(1);
  
  // Write initial diagnose to serial port
  Serial.println("");
  Serial.println("Hello, this is T-Dongle-S3.");
  Serial.println("I'm alive and well");
  Serial.println("");

  // Turn off LCD backlight
  pinMode(TFT_LEDA_PIN, OUTPUT);  
  digitalWrite(TFT_LEDA_PIN, 0);  

  // Attach LED
  FastLED.addLeds<APA102, LED_DI_PIN, LED_CI_PIN, BGR>(&leds, 1);  

  // Attach handler to the button
  button.attachClick(button_pressed);
  button.attachLongPressStart(button_pressed);

  // Create a separate task for the button to be checked. Task is pinned to core #0
  // Note that the main loop runs on core #1. Priority of the task is set to 1, which is above the iddle task (0)
  xTaskCreatePinnedToCore(button_task, "button_task", 1024, NULL, 1, NULL, 0);
}

// ------------------------------------------------------------------------------------

void loop() {
  FastLED.showColor(CRGB::Red);  
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, TFT_RED);
  tft.setTextColor(TFT_WHITE, TFT_RED);
  tft.drawString("RED", TFT_HEIGHT/2, TFT_WIDTH/2, 4);
  Serial.println("Red");
  delay(1000);

  FastLED.showColor(CRGB::Green);
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, TFT_GREEN);
  tft.setTextColor(TFT_BLACK, TFT_GREEN);
  tft.drawString("GREEN", TFT_HEIGHT/2, TFT_WIDTH/2, 4);
  Serial.println("Green");
  delay(1000);
  
  FastLED.showColor(CRGB::Blue);
  tft.fillRect(0, 0, TFT_HEIGHT, TFT_WIDTH, TFT_BLUE);
  tft.setTextColor(TFT_WHITE, TFT_BLUE);
  tft.drawString("BLUE", TFT_HEIGHT/2, TFT_WIDTH/2, 4);
  Serial.println("Blue");
  delay(1000);
}
