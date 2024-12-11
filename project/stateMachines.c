#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "libTimer.h"
#include "triangle.h"
#include "lcdutils.h"
#include "lcddraw.h"

void state_control(int state){

  int centerX = screenWidth/2;
  int centerY = screenHeight/2;
  int size = 25;

  switch(state){

  case 1:

    led_init(0);
    song1();
    clearScreen(COLOR_BLUE);
    drawUp(centerX,centerY,size,COLOR_YELLOW);
   
    //add music
    //add image

    break;

  case 2:
    led_init(1);
    song2();
    clearScreen(COLOR_BLACK);
    drawDown(centerX,centerY,size,COLOR_RED);
    //add words
    //add music

    break;

  case 3:

    //add image on display
    led_init(0);
    song3();
    clearScreen(COLOR_RED);
    drawLeft(centerX,centerY,size,COLOR_BLUE);


    break;

  case 4:
    led_init(1);
    song4();
    clearScreen(COLOR_BROWN);
    drawRight(centerX,centerY,size,COLOR_GREEN);

    break;

  default:
    clearScreen(COLOR_WHITE);

   
    break;

  }




}
