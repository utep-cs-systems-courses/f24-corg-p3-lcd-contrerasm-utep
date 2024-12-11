#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "switches.h"



char switch_state_down;



void switch_init()

{

  P2REN |= SWITCHES; //enables resistors for switches
  P2IE |= SWITCHES;  //enable interrupts from switches
  P2OUT |= SWITCHES; // activates pull ups for switches
  P2DIR &= ~SWITCHES; //enable switch pins as input pins

}//end of swithc_init



char switch_update_interrupt_sense()

{
  char p2val =P2IN;//used to read the input val from P2
  P2IES |= (p2val & SWITCHES); //switch up, sense down. used to detect is switch is pressed
  P2IES &= (p2val | ~SWITCHES); //if switch down sense is up.used to detect if switch is released
  return p2val;//return the current val of P2

}//end of swith_update_interrupt_sense



void switch_interrupt_handler()

{
  char p2val = switch_update_interrupt_sense();//used to read the current input from P2
  
  //the following lines are used to check if their assigned buttons have been pressed
  char button1 = (p2val & sw1) ? 0:sw1;
  char button2 = (p2val & sw2) ? 0:sw2;
  char button3 = (p2val & sw3) ? 0:sw3;
  char button4 = (p2val & sw4) ? 0:sw4;

  if(button1)

    {
      state_control(1);//used to call state 1 from statemachines.C
      switch_state_down=1;//button is pressed
    }

  else if(button2)

    {
      state_control(2);
      switch_state_down=1;

    }

  else if(button3)

    {

      state_control(3);
      switch_state_down=1;

    }

  else if(button4)

    {

      state_control(4);
      switch_state_down=1;

    }

}//end of switch_interrupt_handler
