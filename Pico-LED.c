#include "System-Functions/include/System-Functions.h"
#include "Colour Functions.h"
#include "Constants.h"

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
