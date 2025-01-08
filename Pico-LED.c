#include "System-Functions/include/System-Functions.h"
#include "Colour Functions.h"
#include "Constants.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "C:\Users\spara\Documents\Pico LED\Pico-LED\build\pico-sdk\src\rp2_common\pico_multicore\multicore.c"

/*
void core1_entry() {
  rainbowLights(100, 0, STRIP_1_PIXELS);
}

void core2_entry() {
  fadingLights(255, 255, 255, 100, 1, STRIP_2_PIXELS);
}
*/
/*
int main() {
  setup();
  turnOffAllLights(0, STRIP_1_PIXELS);
  turnOffAllLights(1, STRIP_2_PIXELS);
  multicore_launch_core1(core2_entry);

  core1_entry();

}
*/

void emitStaticColourAllCore1() {
  emitStaticColourAll(r, g, b, 100, 1, STRIP_2_PIXELS);
  enterSleep();
}

void flashingLightsCore1() {
  flashingLights(r, g, b, 100, 1, STRIP_2_PIXELS, false);
}

void rainbowLightsCore1() {
  rainbowLights(100, 1, STRIP_2_PIXELS, false);
}

void fadingLightsCore1() {
  fadingLights(r, g, b, 100, 1, STRIP_2_PIXELS, false);
}

void patternLightsCore1() {
  patternLights(r, g, b, 100, 1, STRIP_2_PIXELS, false);
}

void blueAndOrangeCore1() {
  blueAndOrange(1, STRIP_2_PIXELS, false);
}

void colourFunctionsForCore1() {
    switch (mode)
    {
    case 1:
      multicore_launch_core1(emitStaticColourAllCore1);
      break;
    case 2:
      multicore_launch_core1(flashingLightsCore1);
      break;
    case 3:
      multicore_launch_core1(rainbowLightsCore1);
      break;
    case 4:
      multicore_launch_core1(fadingLightsCore1);
      break;
    case 5:
      multicore_launch_core1(patternLightsCore1);
      break;
    case 6:
      multicore_launch_core1(blueAndOrangeCore1);
      break;
    default:
      break;
    }
}

int main()
{
  setup();
  turnOffAllLights(0, STRIP_1_PIXELS);
  turnOffAllLights(1, STRIP_2_PIXELS);
  __wfe();

  while (1)
  {
    printValues();
    measure_freqs();

    irq_flag = uartContainsData = false;
    direction = true;

    switch (mode)
    {
    case 0:
      break;
    case 1:
      emitStaticColourAll(r, g, b, 100, 0, STRIP_1_PIXELS);
      enterSleep();
      break;
    case 2:
      flashingLights(r, g, b, brightness, 0, STRIP_1_PIXELS, true);
      break;
    case 3:
      rainbowLights(brightness, 0, STRIP_1_PIXELS, true);
      break;
    case 4:
      fadingLights(r, g, b, brightness, 0, STRIP_1_PIXELS, true);
      break;
    case 5:
      patternLights(r, g, b, brightness, 0, STRIP_1_PIXELS, true);
      break;
    case 6:
      blueAndOrange(0, STRIP_1_PIXELS, true);
      break;
    default:
      break;
    }

  }
}
