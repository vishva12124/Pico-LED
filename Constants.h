#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define UART_ID uart1
#define BAUD_RATE 1000
#define UART_RX_PIN 9
#define WS2812_PIN 2
#define IRQ_PIN 3
#define SLEEP_PIN 4
#define PIXELS 20

uint8_t rgb[2];

uint8_t stripNumber = 0;

const char NUM_PIXELS = 20;

const uint32_t rainbowLightDelay = 20; 
const uint32_t fadingLightDelay = 2;
const uint32_t patternLightDelay = 30;
const uint32_t flashingLightDelay = 500;
const uint32_t blueAndOrangeDelay = 500;

bool irq_flag = false, direction = true, isUartReadable = false;
uint8_t r, g, b, mode, brightness,
        scb_orig, clock0_orig, clock1_orig;

#endif