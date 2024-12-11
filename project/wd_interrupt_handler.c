#include <msp430.h>

#include "stateMachines.h"


/*msp430 interrupts ever 125 miliseconds, for 5 seconds increase the treshold to 250 and count to 40*/
  void

__interrupt_vec(WDT_VECTOR) WDT(){ /*250 interrupts*/
  
  static char blink_count =0;//used to tracck number of interrupts

  if (++blink_count ==125){//used to determine if half a second has passed

    blink_count =0;

  }

}
