#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "Constants.h"

uint8_t rgb[2],
    

void printValues()
{
    printf("Brightness: %d\n", brightness);
    printf("Mode: %d\n", mode);
    printf("R: %d\n", r);
    printf("G: %d\n", g);
    printf("B: %d\n", b);
}
*/

void getUserInput() {
    uart_read_blocking(UART_ID, &buffer, 1);
    uart_read_blocking(UART_ID, (int *) &mode, 1);
    uart_read_blocking(UART_ID, (int *) &r, 2);
    r = buffer[0] + buffer[1];
    uart_read_blocking(UART_ID, (int *) &g, 2);
    g = buffer[0] + buffer[1];
    uart_read_blocking(UART_ID, (int *) &b, 2);
    r = buffer[0] + buffer[1];
}

void interrupt()
{
    irq_flag = true;
}

void resetVariables() {
    irq_flag = false, direction = true;
    brightness = mode = r = g = b = 0;
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