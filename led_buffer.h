#include "ws2812.pio.h"
#include "Constants.h"

struct LEDValues {
    int r;
    int g;
    int b;
};

struct LEDValues RGB[PIXELS];

static inline void put_pixel(uint32_t pixel_grb)
{
  pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
  return ((uint32_t)(r) << 8) |
         ((uint32_t)(g) << 16) |
         (uint32_t)(b);
}

void storeLEDValues(int pixelIndex, int r, int g, int b) {
  RGB[pixelIndex].r = r;
  RGB[pixelIndex].g = g;
  RGB[pixelIndex].b = b;
}

void setColour()
{
  sleep_ms(3);
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    uint32_t colour_set = urgb_u32((RGB[i].r), (RGB[i].g), (RGB[i].b));
    put_pixel(colour_set);
  }
}
