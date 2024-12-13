#include <msp430.h>
#include "led.h"

void led_init(int on){
  P1DIR |= LED;
  if(on){
    P1OUT |=LED;//turn on
  }else{
    P1OUT &= ~LED;//turn off
  }
  }
