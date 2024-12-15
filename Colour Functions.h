#include "Constants.h"

void emitStaticColourAll(int r, int g, int b, int brightness)
{
  for (int x = 0; x != NUM_PIXELS; x++) {
    storeLEDValues(x, r, g, b);
  }
  setColour();
}

void emitStaticColour(int r, int g, int b, int ledIndex, int brightness)
{
  storeLEDValues(ledIndex, r, g, b);
  setColour();
}

void turnOffAllLights()
{
  for (int x = 0; x < NUM_PIXELS; x++)
  {
    storeLEDValues(x, 0, 0, 0);
  }
  setColour();
}

void flashingLights(int r, int g, int b, int brightness)
{
  while (irq_flag == false)
  {
    emitStaticColourAll(r, g, b, brightness);
    sleep_ms(flashingLightDelay);
    turnOffAllLights();
    sleep_ms(flashingLightDelay);
  }
}

void rainbowLights(int brightness) {
  while (irq_flag == false) {
    for (int x = 0; x < 254; x++) {
      emitStaticColourAll(x, ((x + 85) % 255), ((x + 170) % 255), 100);
      sleep_ms(rainbowLightDelay);
    }    
  }
}

void fadingLights(int r, int g, int b, int brightness)
{
  
  while (irq_flag == false) {
    for (int x = 0; x != 250; x++) {
        r--;
        g--;
        b--;
        emitStaticColourAll(r, g, b, 100);
        sleep_ms(fadingLightDelay);
    }
    for (int x = 250; x > 0; x--) {
        r++;
        g++;
        b++;
        emitStaticColourAll(r, g, b, 100);
        sleep_ms(fadingLightDelay);
    }    
  }
}


void patternLights(int r, int g, int b, int brightness)
{
  turnOffAllLights();
  emitStaticColour(r, g, b, 0, 100);
  while (irq_flag == false) {

    for (int x = 1; x < NUM_PIXELS; x++) {
      sleep_ms(patternLightDelay);
      emitStaticColour(r, g, b, x, 100);
      emitStaticColour(0, 0, 0, x - 1, 100);
    }
    for (int x = NUM_PIXELS; x >= 0; x--) {
      sleep_ms(patternLightDelay);
      emitStaticColour(r, g, b, x - 1, 100);
      emitStaticColour(0, 0, 0, x, 100);
    }    
  }
}
