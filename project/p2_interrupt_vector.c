#include <msp430.h>
#include "switches.h"

//this is used to detect if a button was pressed on the display board

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){//did a button cause an interuption
    P2IFG &= ~SWITCHES;//clear any pending switch interrupts
    switch_interrupt_handler();//main handler for all swiches
  }
}//end of interrupt_vec
