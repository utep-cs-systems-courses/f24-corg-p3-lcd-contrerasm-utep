#ifndef led_included
#define led_included

#include <msp430.h>

#define LED BIT6; //BIT0 for display

void led_init(int on);

#endif
