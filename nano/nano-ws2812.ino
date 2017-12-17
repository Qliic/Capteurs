// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
// https://github.com/adafruit/Adafruit_NeoPixel

#include <Adafruit_NeoPixel.h>

#define PIN            3
#define NUMPIXELS      3

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void loop() {
    int r, g, b, d;

    r = random(0,64);
    g = random(0,64);
    b = random(0,64);
    d = random(10);

    pixels.setPixelColor(0, pixels.Color(r,0,b));
    pixels.setPixelColor(1, pixels.Color(0,b,r));
    pixels.setPixelColor(2, pixels.Color(b,r,0));
    pixels.show();
    
    delay(100*d);
}
