#include <FastLED.h>

#define LED_PIN 6
#define NUM_LEDS 288

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  for(int i =0;i<288;i++){
      leds[i] = CRGB(100, 0, 0);
  FastLED.show();
  delay(100);

  }

}
