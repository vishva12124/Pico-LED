#ifndef led_buffer_H_
#define led_buffer_H_

#include "ws2812.pio.h"
#include "Constants.h"
#include "pico/stdlib.h"

struct LEDValues {
    int r;
    int g;
    int b;
};

struct LEDValues STRIP_1_RGB[STRIP_1_PIXELS];
struct LEDValues STRIP_2_RGB[STRIP_2_PIXELS];

static inline void put_pixel(uint32_t pixel_grb, PIO pioID, int sm)
{
  pio_sm_put_blocking(pioID, sm, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)(r) << 8) |
         ((uint32_t)(g) << 16) |
         (uint32_t)(b);
}

void storeLEDValues(uint pixelIndex, uint8_t r, uint8_t g, uint8_t b, uint stripNumber) {
  if (stripNumber == 0) {
    STRIP_1_RGB[pixelIndex].r = r;
    STRIP_1_RGB[pixelIndex].g = g;
    STRIP_1_RGB[pixelIndex].b = b;
  }
  else if (stripNumber == 1) {
    STRIP_2_RGB[pixelIndex].r = r;
    STRIP_2_RGB[pixelIndex].g = g;
    STRIP_2_RGB[pixelIndex].b = b;
  }  
}

void setColour(PIO pioID, int sm, uint8_t pixelCount, int stripNumber)
{
  sleep_ms(1);
  uint32_t colour_set;
  for (int i = 0; i < pixelCount; i++)
  {
    if (stripNumber == 0) {
      colour_set = urgb_u32((STRIP_1_RGB[i].r), (STRIP_1_RGB[i].g), (STRIP_1_RGB[i].b));
    }
    else if (stripNumber ==  1) {
      colour_set = urgb_u32((STRIP_2_RGB[i].r), (STRIP_2_RGB[i].g), (STRIP_2_RGB[i].b));
    }
    put_pixel(colour_set, pioID, sm);
  }
}

#endif