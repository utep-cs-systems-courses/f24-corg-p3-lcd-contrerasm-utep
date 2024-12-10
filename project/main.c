#include <msp430.h>
#include <stdio.h>
#include <libTimer.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcddraw.h"
#include "lcdutils.h"
#include "stateMachines.h"
#include "led.h"


int main(void)

{
  configureClocks();
  lcd_init();
  switch_init();//switches
  led_init();//GREEN on
  buzzer_init();//Buzzer
  enableWDTInterrupts();
  or_sr(0x18); //cpu off, GIE on

}
