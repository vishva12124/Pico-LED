#include "led_buffer.h"
#include "Colour Functions.h"
#include "Constants.h"
#include "pico/stdlib.h"
#include "System Functions.h"

int main()
{

  setup();

  while (true)
  {
    if (uart_is_readable(UART_ID))
    {
      turnOffAllLights();
      irq_flag = false, direction = true;
      brightness = mode = r = g = b = i = 0;
      brightness = uart_getc(UART_ID);
      mode = uart_getc(UART_ID);
      r = uart_getc(UART_ID);
      g = uart_getc(UART_ID);
      b = uart_getc(UART_ID);

      printValues();

      if (brightness == 0) {
        if (mode == 5) {
          turnOffAllLights();
        }
        else {
          emitStaticColourAll(0, 0, 0, 0);
        }
      }

      else if (mode == 1)
      {
        emitStaticColourAll(r, g, b, 100);
        sleep_ms(0);
        emitStaticColourAll(r, g, b, 100);

      }

      else if (mode == 2)
      {
        flashingLights(r, g, b, brightness);
      }

      else if (mode == 3)
      {
        rainbowLights(brightness);
      }

      else if (mode == 4)
      {
        fadingLights(r, g, b, brightness);
      }

      else if (mode == 5)
      {
        patternLights(r, g, b, brightness);
      }
    }
  }
}