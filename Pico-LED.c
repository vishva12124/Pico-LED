#include "System-Functions/include/System-Functions.h"
#include "Colour Functions.h"
#include "Constants.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "C:\Users\spara\Documents\Pico LED\Pico-LED\build\pico-sdk\src\rp2_common\pico_multicore\multicore.c"

void core1_entry() {
  rainbowLights(100, 0, STRIP_1_PIXELS);
}

void core2_entry() {
  fadingLights(255, 255, 255, 100, 1, STRIP_2_PIXELS);
}

int main() {
  setup();
  turnOffAllLights(0, STRIP_1_PIXELS);
  turnOffAllLights(1, STRIP_2_PIXELS);
  multicore_launch_core1(core2_entry);

  core1_entry();

}

/*
int main()
{
  setup();
  turnOffAllLights(0);
  turnOffAllLights(1);
  getUserInput();
  
  while (1)
  {
    turnOffAllLights(0);
    turnOffAllLights(1);
    printValues();
    measure_freqs();

    irq_flag = uartContainsData = false;
    direction = true;

    switch (mode)
    {
    case 1:
      emitStaticColourAll(r, g, b, 100, stripNumber);
      enterSleep();
      break;
    case 2:
      flashingLights(r, g, b, brightness, stripNumber);
      break;
    case 3:
      rainbowLights(brightness, stripNumber);
      break;
    case 4:
      fadingLights(r, g, b, brightness, stripNumber);
      break;
    case 5:
      patternLights(r, g, b, brightness, stripNumber);
      break;
    case 6:
      blueAndOrange(stripNumber);
      break;
    default:
      break;
    }
  }
}
*/