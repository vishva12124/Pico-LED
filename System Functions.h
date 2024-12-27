#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "Constants.h"
#include <stdio.h>
#include <hardware/structs/rosc.h>
#include "pico-extras/src/rp2_common/pico_sleep/include/pico/sleep.h"
#include "build/pico-sdk/src/rp2_common/pico_runtime_init/include/pico/runtime_init.h"
    
void printValues()
{
    printf("\nBrightness: %d\n", brightness);
    printf("Mode: %d\n", mode);
    printf("R: %d\n", r);
    printf("G: %d\n", g);
    printf("B: %d\n", b);
}

void getUserInput() {

    uart_read_blocking(UART_ID, (uint8_t *)&stripNumber, 1);
    uart_read_blocking(UART_ID, (uint8_t *)&brightness, 1);
    uart_read_blocking(UART_ID, (uint8_t *) &mode, 1);
    uart_read_blocking(UART_ID, rgb, 2);
    r = rgb[0] + rgb[1];
    uart_read_blocking(UART_ID, rgb, 2);
    g = rgb[0] + rgb[1];
    uart_read_blocking(UART_ID, rgb, 2);
    b = rgb[0] + rgb[1];
    printf("\nInterrupt received");
    irq_flag = isUartReadable = true;
}

void interrupt()
{
    printf("\nInterrupt received");
    irq_flag = true;
}

void resetVariables() {
    direction = true;
    brightness = mode = r = g = b = 0;
}


void setup() {
  stdio_init_all();
  PIO pio = pio0;
  int sm = 0;
  int sm2 = 1;
  uint offset = pio_add_program(pio, &ws2812_program);
  pio_sm_set_enabled(pio, sm, false);
  ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
  ws2812_program_init(pio, sm2, offset, 0, 800000, false);

  //gpio_init(IRQ_PIN);
  //gpio_set_dir(IRQ_PIN, GPIO_IN);
  //gpio_pull_down(IRQ_PIN);
  //gpio_set_irq_enabled(IRQ_PIN, GPIO_IRQ_EDGE_RISE, false);
  //gpio_set_irq_enabled_with_callback(IRQ_PIN, GPIO_IRQ_EDGE_RISE, true, interrupt);

  gpio_init(SLEEP_PIN); 
  gpio_set_dir(SLEEP_PIN, GPIO_IN);
  gpio_pull_down(SLEEP_PIN);
  
  //pll_deinit(pll_usb);
  

  //gpio_init(25);
  //gpio_set_dir(25, GPIO_OUT);
  
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  irq_set_exclusive_handler(UART1_IRQ, getUserInput);
  irq_set_enabled(UART1_IRQ, true);
  uart_set_irqs_enabled(UART_ID, true, false);  
} 

void enterSleep() {
  sleep_ms(1);
  irq_set_enabled(UART1_IRQ, false);

  sleep_run_from_xosc();

  sleep_goto_dormant_until_edge_high(SLEEP_PIN);
  sleep_goto_dormant_until_edge_high(true);

  sleep_power_up();

  sleep_ms(100);
  resetVariables();

  setup();
  
  turnOffAllLights();
  sleep_ms(1);
}  