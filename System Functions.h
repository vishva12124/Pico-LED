#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "Constants.h"
#include <stdio.h>
#include <hardware/structs/rosc.h>
#include "pico-extras/src/rp2_common/pico_sleep/include/pico/sleep.h"
#include "build/pico-sdk/src/rp2_common/pico_runtime_init/include/pico/runtime_init.h"

uint8_t rgb[2];
    
void printValues()
{
    printf("\nBrightness: %d\n", brightness);
    printf("Mode: %d\n", mode);
    printf("R: %d\n", r);
    printf("G: %d\n", g);
    printf("B: %d\n", b);
}

    uint32_t f_pll_sys;
    uint32_t f_pll_usb;
    uint32_t f_rosc;
    uint32_t f_clk_sys; 
    uint32_t f_clk_peri;
    uint32_t f_clk_usb;
    uint32_t f_clk_adc;
    uint32_t f_clk_rtc;

void printClocks() {
    f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
    f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);

    printf("pll_sys  = %dkHz\n", f_pll_sys);
    printf("pll_usb  = %dkHz\n", f_pll_usb);
    printf("rosc     = %dkHz\n", f_rosc);
    printf("clk_sys  = %dkHz\n", f_clk_sys);
    printf("clk_peri = %dkHz\n", f_clk_peri);
    printf("clk_usb  = %dkHz\n", f_clk_usb);
    printf("clk_adc  = %dkHz\n", f_clk_adc);
    printf("clk_rtc  = %dkHz\n", f_clk_rtc);
}

void compareClocks() {
    uint32_t g_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    uint32_t g_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    uint32_t g_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    uint32_t g_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    uint32_t g_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    uint32_t g_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    uint32_t g_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
    uint32_t g_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);
    
    if (g_pll_sys != f_pll_sys) {
        //gpio_put(25, true); //works 
    }
    if (g_pll_usb != f_pll_usb) {
        //gpio_put(25, true); //works
    }
    if (g_rosc > f_rosc) {
        gpio_put(25, true); //DOES NOT WORK
    }    
    if (g_clk_sys != f_clk_sys) {
        //gpio_put(25, true); //works
    }    
    if (g_clk_peri != f_clk_peri) {
        //gpio_put(25, true); //works
    }
    if (g_clk_usb != f_clk_usb) {
        //gpio_put(25, true); //works 
    }
    if (g_clk_adc != f_clk_adc) {
        //gpio_put(25, true); //works
    }
    if (g_clk_rtc != f_clk_rtc) {
        //gpio_put(25, true); //works
    }                            
}

void getUserInput() {
    uart_read_blocking(UART_ID, (uint8_t *)&brightness, 1);
    uart_read_blocking(UART_ID, (uint8_t *) &mode, 1);
    uart_read_blocking(UART_ID, rgb, 2);
    r = rgb[0] + rgb[1];
    uart_read_blocking(UART_ID, rgb, 2);
    g = rgb[0] + rgb[1];
    uart_read_blocking(UART_ID, rgb, 2);
    b = rgb[0] + rgb[1];
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

void enterSleep() {
  scb_orig = scb_hw->scr;
  clock0_orig = clocks_hw->sleep_en0;
  clock1_orig = clocks_hw->sleep_en1;

  sleep_run_from_xosc();

  sleep_goto_dormant_until_edge_high(IRQ_PIN);

  rosc_write(&rosc_hw->ctrl, ROSC_CTRL_ENABLE_BITS);
  scb_hw->scr = scb_orig;
  clocks_hw->sleep_en0 = clock0_orig;
  clocks_hw->sleep_en1 = clock1_orig;

  clocks_init();
  stdio_init_all();
  //setup();
}  