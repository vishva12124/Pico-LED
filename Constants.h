#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define UART_ID uart0
#define BAUD_RATE 9600
#define UART_RX_PIN 1
#define WS2812_PIN 2
#define IRQ_PIN 3
#define PIXELS 20

const int NUM_PIXELS = 20;

const int rainbowLightDelay = 20; 
const int fadingLightDelay = 2;
const int patternLightDelay = 30;
const int flashingLightDelay = 500;

bool irq_flag = false, direction = true;
float i, constant, r, g, b;
int mode, brightness, step, stringy[5];

#endif