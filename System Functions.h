#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "Constants.h"

void interrupt()
{
    irq_flag = true;
}

void setup()
{
    stdio_init_all();
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, false);
    gpio_set_dir(IRQ_PIN, GPIO_OUT);
    gpio_pull_down(IRQ_PIN);
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_irq_enabled_with_callback(IRQ_PIN, GPIO_IRQ_EDGE_RISE, true, interrupt);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void printValues()
{
    sprintf(stringy, "%d", brightness);
    printf(stringy);
    printf("\nBrightness:\n\n");

    sprintf(stringy, "%d", mode);
    printf(stringy);
    printf("\nMode:\n\n");

    sprintf(stringy, "%d", r);
    printf(stringy);
    printf("\nR:\n\n");

    sprintf(stringy, "%d", g);
    printf(stringy);
    printf("\nG:\n\n");

    sprintf(stringy, "%d", b);
    printf(stringy);
    printf("\nB:\n\n");
}