#ifndef switches_included
#define switches_included

//the following are used to define the switches connected to msp430
#define sw1 BIT0 
#define sw2 BIT1 
#define sw3 BIT2
#define sw4 BIT3

#define SWITCHES (sw1|sw2|sw3|sw4)//we will used to check the status of the switches



void switch_init();
static char switch_update_interrupt_sense();
void switch_interrupt_handler();



extern char switch_state_changed;
extern char switch_state_down;
extern char button_sequence_state;
extern int secondCount;


#endif//included
