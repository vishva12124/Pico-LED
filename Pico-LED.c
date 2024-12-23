#include "Colour Functions.h"
#include "System Functions.h"
#include "Constants.h"

void runColourFunctions()
{
  while (true) {
  if (uart_is_readable(UART_ID))
  {
    turnOffAllLights();
    resetVariables();
    getUserInput();
    printValues();

    switch(mode) {
      case 1:
        printClocks();
        emitStaticColourAll(r, g, b, 100);
        enterSleep();
        gpio_put(25, true);
        //compareClocks();
        r = g = b = 255;
        brightness = 100;
        irq_flag = false;
        //break;
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
  while (true)
  {
    runColourFunctions();
  }
}