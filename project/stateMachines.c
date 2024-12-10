#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "libTimer.h"
#include "triangle.h"
#include "lcdutils.h"

void state_control(int state){

  int centerX = screenWidth/2;
  int centerY = screenHeight/2;
  int size = 25;

  switch(state){

  case 1:

    song1();
    drawUp(centerX,centerY,size,COLOR_ORANGE);
   
    //add music
    //add image

    break;

  case 2:

    song2();
    
    //add words
    //add music

    break;

  case 3:

    //add image on display

    song3();


    break;

  case 4:
    
    song4();

    break;

  default:

   
    break;

  }




}
