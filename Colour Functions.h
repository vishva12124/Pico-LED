
#include "led_buffer.h"
#include "Constants.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

struct LEDValues rainbow;

void emitStaticColourAll(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  for (uint8_t x = 0; x != NUM_PIXELS; x++) {
    storeLEDValues(x, r, g, b);
  }
  setColour();
}

void emitStaticColour()
{
  setColour();
}

void turnOffAllLights()
{
  for (uint8_t x = 0; x < NUM_PIXELS; x++)
  {
    storeLEDValues(x, 0, 0, 0);
  }
  setColour();
}

/*
void flashingLights(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  while (irq_flag != true)
  {
    emitStaticColourAll(r, g, b, brightness);
    sleep_ms(flashingLightDelay);
    turnOffAllLights();
    sleep_ms(flashingLightDelay);
  }
}
*/

void flashingLights(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  while (irq_flag != true) {
    gpio_put(25, true);
    sleep_ms(flashingLightDelay);
    gpio_put(25, false);
    sleep_ms(flashingLightDelay);
  }
}

void updateRGBValues(double time, double frequency) {
  double r_translation = 0.002, g_translation = 1.3, b_translation = 3.1;
  rainbow.r = pow((127.5 * (cos(frequency * time + r_translation) + 1)), 0.999);
  rainbow.g = pow((127.5 * (cos(frequency * time + g_translation) + 1)), 0.999);
  rainbow.b = pow((127.5 * (cos(frequency * time + b_translation) + 1)), 0.999);
}
void rainbowLights(uint8_t brightness) {
  double startTime = time_us_32();  
  while (irq_flag == false) {
    double timeDifference = time_us_32() - startTime;
    updateRGBValues(timeDifference, 0.005);
    emitStaticColourAll(rainbow.r, rainbow.g, rainbow.b, 100);
    sleep_ms(40);
  }
}


void fadingLights(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  
  while (irq_flag == false) {
    for (uint8_t x = 0; x != 250; x++) {
      switch (r) {
        case 0:
          break;
        default:
          r--;
          break;
      }
      switch (g) {
        case 0:
          break;
        default:
          g--;
          break;
      }
      switch (b) {
        case 0:
          break;
        default:
          b--;
          break;
      }  
        emitStaticColourAll(r, g, b, 100);
        sleep_ms(fadingLightDelay);
    }
    for (uint8_t x = 250; x > 0; x--) {
      switch (r) {
        case 0:
          break;
        default:
          r++;
          break;
      }
      switch (g) {
        case 0:
          break;
        default:
          g++;
          break;
      }
      switch (b) {
        case 0:
          break;
        default:
          b++;
          break;
      }  
        emitStaticColourAll(r, g, b, 100);
        sleep_ms(fadingLightDelay);
    }    
  }
}

void blueAndOrange() {
while (irq_flag == false) {
  emitStaticColourAll(0, 0, 255, 100);
  sleep_ms(blueAndOrangeDelay);
  emitStaticColourAll(255, 106, 10, 100);
  sleep_ms(blueAndOrangeDelay);
}

}


void patternLights(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness)
{
  turnOffAllLights();
  uint8_t x = 0, i = 1;
  direction = true;
  while (irq_flag == false)
  {
    storeLEDValues(i, r, g, b);
    emitStaticColour();
    storeLEDValues(x, 0, 0, 0);
    emitStaticColour();
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

    switch (direction) {
      case 0:
        i--;
        x--;
        break;
      case 1:
        i++;
        x++;
        break;
    }
  }
}