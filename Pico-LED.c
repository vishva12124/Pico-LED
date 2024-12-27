#include "Colour Functions.h"
#include "System Functions.h"
#include "Constants.h"

void runColourFunctions()
{
  while (true)
  {
    if (uart_is_readable(UART_ID))
    {
      turnOffAllLights();
      resetVariables();
      getUserInput();
      printValues();

      switch (mode)
      {
      case 1:
        emitStaticColourAll(r, g, b, 100);
        enterSleep();
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
      case 6:
        blueAndOrange();
        break;
      default:
        break;
      }
    }
  }
}
int main()
{
  setup();
  turnOffAllLights();
  while (true)
  {
    runColourFunctions();
  }
}