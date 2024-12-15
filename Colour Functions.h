
#include "led_buffer.h"
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
  while (irq_flag != true)
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
  i = 1;
  int x = 0;
  direction = true;
  while (irq_flag == false)
  {
    emitStaticColour(r, g, b, i, brightness);
    emitStaticColour(0, 0, 0, x, brightness);
    sleep_ms(patternLightDelay);
    if (i == NUM_PIXELS)
    {
      direction = false;
      x = NUM_PIXELS + 1;
    }
    else if (i == 0 && direction == false)
    {
      direction = true;
      x = -1;
    }
    if (direction == false)
    {
      i--;
      x--;
    }
    else if (direction == true)
    {
      i++;
      x++;
    }
  }
}