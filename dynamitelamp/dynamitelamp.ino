#include <Adafruit_NeoPixel.h>
#include <DMXSerial.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

#define NUM_LEDS 96

#define BRIGHTNESS 50
#define DMXSPEED       115200

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte pixelBuffer[384];


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  for(int i=0; i<384; i++) pixelBuffer[i]=i;
  DMXSerial.init(DMXReceiver);
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  
  if (Serial.available() > 0) {
    // get incoming byte:
    Serial.readBytes(pixelBuffer, 384);
    
      for(uint16_t i=0; i<strip.numPixels(); i+4) {
          strip.setPixelColor(i, strip.Color(pixelBuffer[i],pixelBuffer[i+1],pixelBuffer[i+2], pixelBuffer[i+3] ) );
          //strip.setPixelColor(i, strip.Color(0,0,0, 255 ) );
        }
        //delay(wait);
        strip.show();
  }


}


