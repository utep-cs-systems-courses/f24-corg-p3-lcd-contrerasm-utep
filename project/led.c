#include <msp430.h>
#include "led.h"
#include "switches.h"

void led_init(int on){
  P1DIR |= LED;//used to control the pin layout on p1,LED #64
  if(on){
     P1OUT |= LED;//used to turn on LED
  }else{
    P1OUT &= ~LED;//used to turn off LED
  }
}
