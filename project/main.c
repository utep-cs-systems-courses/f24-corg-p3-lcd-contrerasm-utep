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
  configureClocks();//used to for msp430 clock
  lcd_init();//initializes lcd
  clearScreen(COLOR_GREEN);//set the screen to green at start
  switch_init();//initialized swtiches
  led_init(0);//used to control led
  buzzer_init();//initiazlizes buzzer
  enableWDTInterrupts();//used to enable interrupts
  
  or_sr(0x18); //cpu off, GIE on

}
