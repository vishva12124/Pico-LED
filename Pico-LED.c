#include "Colour Functions.h"
#include "System Functions.h"
#include "Constants.h"

void runColourFunctions()
{
  if (uart_is_readable(UART_ID))
  {
    turnOffAllLights();
    irq_flag = false, direction = true;
    brightness = mode = r = g = b = i = 0;

    getUserInput();
    printValues();

    switch(mode) {
      case 1:
        emitStaticColourAll(r, g, b, 100);
        break;
      case 2:
        flashingLights(r, g, b, brightness);
        break;
      case 3:
        rainbowLights(brightness);
        break;
      case 4:
        fadingLights(r, g, b, brightness);
        break;
      case 5:
        patternLights(r, g, b, brightness);
        break;
    }
  }
}

int main()
{
  setup();
  while (true)
  {
    runColourFunctions();
  }
}