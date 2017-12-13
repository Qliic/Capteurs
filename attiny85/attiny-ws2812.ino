#include <Adafruit_NeoPixel.h>

#define PIN            1
#define NUMPIXELS      1
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
    pixels.setPixelColor(0, pixels.Color(150,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).

    pixels.setPixelColor(0, pixels.Color(0,150,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).

    pixels.setPixelColor(0, pixels.Color(0,0,150));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).

    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).
}
