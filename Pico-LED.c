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

    brightness = uart_getc(UART_ID);
    mode = uart_getc(UART_ID);
    r = uart_getc(UART_ID);
    g = uart_getc(UART_ID);
    b = uart_getc(UART_ID);

    printValues();

    if (mode == 1)
    {
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

int main()
{
  stdio_init_all();
  PIO pio = pio0;
  int sm = 0;
  uint offset = pio_add_program(pio, &ws2812_program);
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
  gpio_set_dir(IRQ_PIN, GPIO_IN);
  gpio_init(25);
  gpio_set_dir(25, GPIO_OUT);
  gpio_pull_down(IRQ_PIN);
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_irq_enabled_with_callback(IRQ_PIN, GPIO_IRQ_EDGE_RISE, true, interrupt);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  while (true)
  {
    runColourFunctions();
  }
}