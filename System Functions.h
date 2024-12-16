#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "Constants.h"

void printValues()
{
   
    sprintf(stringy, "%d", brightness);
    printf(stringy);
    printf("\nBrightness:\n\n");

    sprintf(stringy, "%d", mode);
    printf(stringy);
    printf("\nMode:\n\n");

    sprintf(stringy, "%f", r);
    printf(stringy);
    printf("\nR:\n\n");

    sprintf(stringy, "%f", g);
    printf(stringy);
    printf("\nG:\n\n");

    sprintf(stringy, "%f", b);
    printf(stringy);
    printf("\nB:\n\n");
 
}

void getUserInput() {
    brightness = uart_getc(UART_ID);
    mode = uart_getc(UART_ID);
    r = uart_getc(UART_ID);
    g = uart_getc(UART_ID);
    b = uart_getc(UART_ID);    
}

void interrupt()
{
    irq_flag = true;
}

void resetVariables() {
    irq_flag = false, direction = true;
    brightness = mode = r = g = b = i = 0;
}

void setup() {
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
}