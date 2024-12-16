
#include "led_buffer.h"
#include "Constants.h"
#include <math.h>

struct LEDValues rainbow;

void emitStaticColourAll(int r, int g, int b, int brightness)
{
  for (int x = 0; x != NUM_PIXELS; x++) {
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

void getRGBValues(double time, double frequency) {
  int phase_r = 0, phase_g = 2, phase_b = 4;
  rainbow.r = pow((127.5 * (cos(frequency * time + phase_r) + 1)), 1);
  rainbow.g = pow((127.5 * (cos(frequency * time + phase_g) + 1)), 1);
  rainbow.b = pow((127.5 * (cos(frequency * time + phase_b) + 1)), 1);
}

void rainbowLights(int brightness) {
  double startTime = time_us_32();  
  while (irq_flag == false) {
    double timeDifference = time_us_32() - startTime;
    getRGBValues(timeDifference, 0.05);
    emitStaticColourAll(rainbow.r, rainbow.g, rainbow.b, 100);
    sleep_ms(50);
  }
}

void fadingLights(int r, int g, int b, int brightness)
{
  
  while (irq_flag == false) {
    for (int x = 0; x != 250; x++) {
        r = (r == 0) ? (0) : (r-1);
        g = (g == 0) ? (0) : (g-1);
        b = (b == 0) ? (0) : (b-1);
        emitStaticColourAll(r, g, b, 100);
        sleep_ms(fadingLightDelay);
    }
    for (int x = 250; x > 0; x--) {
        r = (r == 0) ? (0) : (r+1);
        g = (g == 0) ? (0) : (g+1);
        b = (b == 0) ? (0) : (b+1);
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