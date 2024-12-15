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

void interrupt()
{
    //ledToggle = !(ledToggle);
    irq_flag = true;
}
