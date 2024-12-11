#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init(int on){
  P1DIR |= LED;
  if(on){
     P1OUT |= LED;//turn on red light
  }else{
    P1OUT &= ~LED;//turn off red light
  }
}
