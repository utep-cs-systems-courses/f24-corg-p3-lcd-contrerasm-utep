#ifndef switches_included

#define switches_included



#define sw1 BIT0

#define sw2 BIT1

#define sw3 BIT2

#define sw4 BIT3



#define SWITCHES (sw1|sw2|sw3|sw4)//4 switches on the board



void switch_init();

static char switch_update_interrupt_sense();

void switch_interrupt_handler();



extern char switch_state_changed;

extern char switch_state_down;

extern char button_sequence_state;

extern int secondCount;



#endif//included
