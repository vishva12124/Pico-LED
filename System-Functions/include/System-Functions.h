#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "Constants.h"
#include <stdio.h>
#include <hardware/structs/rosc.h>
#include "pico-extras/src/rp2_common/pico_sleep/include/pico/sleep.h"
#include "build/pico-sdk/src/rp2_common/pico_runtime_init/include/pico/runtime_init.h"
    
uint f_pll_sys;
uint f_pll_usb; 
uint f_rosc;
uint f_clk_sys;
uint f_clk_peri;
uint f_clk_usb;
uint f_clk_adc;
uint f_clk_rtc; 

void measure_freqs(void) {
    f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
#ifdef CLOCKS_FC0_SRC_VALUE_CLK_RTC
    f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);
#endif
/*
    printf("pll_sys  = %dkHz\n", f_pll_sys);
    printf("pll_usb  = %dkHz\n", f_pll_usb);
    printf("rosc     = %dkHz\n", f_rosc);
    printf("clk_sys  = %dkHz\n", f_clk_sys);
    printf("clk_peri = %dkHz\n", f_clk_peri);
    printf("clk_usb  = %dkHz\n", f_clk_usb);
    printf("clk_adc  = %dkHz\n", f_clk_adc);
#ifdef CLOCKS_FC0_SRC_VALUE_CLK_RTC
    printf("clk_rtc  = %dkHz\n", f_clk_rtc);
#endif
*/
    // Can't measure clk_ref / xosc as it is the ref
}

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
    irq_flag = uartContainsData = true;
}

void resetVariables() {
    direction = true;
    brightness = mode = r = g = b = 0;
}

/*
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


  //gpio_init(SLEEP_PIN); 
  //gpio_set_dir(SLEEP_PIN, GPIO_IN);
  //gpio_pull_down(SLEEP_PIN);
  
  pll_deinit(pll_usb);
  
  //gpio_init(25);
  //gpio_set_dir(25, GPIO_OUT);
  
  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
  //uart_set_format(UART_ID, dataBits, stopBits, parity);

  irq_set_exclusive_handler(UART_IRQ, getUserInput);
  irq_set_enabled(UART_IRQ, true);
  uart_set_irqs_enabled(UART_ID, true, false);  
} 
*/

void setup() {
  stdio_init_all();
  PIO pio = pio0;
  int sm = 0;
  int sm2 = 1;
  uint offset = pio_add_program(pio, &ws2812_program);
  pio_sm_set_enabled(pio, sm, false);
  ws2812_program_init(pio, sm, offset, STRIP_1_PIN, 800000, false);
  ws2812_program_init(pio, sm2, offset, STRIP_2_PIN, 800000, false);
}

void enterSleep() {
  sleep_ms(1);
  irq_set_enabled(UART_IRQ, false);
  uart_deinit(UART_ID);
  gpio_deinit(UART_RX_PIN);
  pio_sm_set_enabled(pio0, 0, false);
  pio_sm_set_enabled(pio0, 1, false);
  stdio_deinit_all();

  sleep_run_from_xosc();
  sleep_goto_dormant_until_edge_high(SLEEP_PIN);

  sleep_power_up();
  gpio_deinit(SLEEP_PIN); 
  sleep_ms(100);
  resetVariables();
  setup();
  turnOffAllLights(0, STRIP_1_PIXELS);
  turnOffAllLights(1, STRIP_2_PIXELS);
  sleep_ms(1);
  getUserInput();
}   