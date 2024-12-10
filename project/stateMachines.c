#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "libTimer.h"


void state_control(int state){

  

  switch(state){

  case 1://turns off both lights

    song1();
   
    //add music
    //add image

    break;

  case 2://flashes red and green

    song2();
    //add words
    //add music

    break;

  case 3://plays jingle

    //add image on display

    song3();


    break;

  case 4:
    //add sound and image
    song4();

    break;

  default:

   
    break;

  }




}
