#include <msp430.h>

#include "timerLib/libTimer.h"

#include "led.h"

#include "buzzer.h"

#include "stateMachines.h"

#include "switches.h"



char switch_state_down;



void switch_init()

{

  P2REN |= SWITCHES; //enables resistors for switches

  P2IE |= SWITCHES;  //enable interrupts from switches

  P2OUT |= SWITCHES; //pull ups for switches

  P2DIR &= ~SWITCHES; //enable switches bits for inputs

}//end of swithc_init



char switch_update_interrupt_sense()

{

  char p2val =P2IN;

  P2IES |= (p2val & SWITCHES); //switch up, sense down

  P2IES &= (p2val | ~SWITCHES); //if switch down sense is up

  return p2val;

}//end of swith_update_interrupt_sense



void switch_interrupt_handler()

{

  char p2val = switch_update_interrupt_sense();

  char button1 = (p2val & sw1) ? 0:sw1;

  char button2 = (p2val & sw2) ? 0:sw2;

  char button3 = (p2val & sw3) ? 0:sw3;

  char button4 = (p2val & sw4) ? 0:sw4;



  if(button1)

    {

      next_state(1);

      switch_state_down=1;

    }

  else if(button2)

    {

      next_state(2);

      switch_state_down=1;

    }

  else if(button3)

    {

      next_state(3);

      switch_state_down=1;

    }

  else if(button4)

    {

      next_state(4);

      switch_state_down=1;

    }

}//end of switch_interrupt_handler
