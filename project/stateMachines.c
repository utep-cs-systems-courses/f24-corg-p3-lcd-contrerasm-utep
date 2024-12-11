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

  int centerX = screenWidth/2; //used to find the center of the screen
  int centerY = screenHeight/2; //used to find the center of the screen
  int size = 25; //used to define the size of the image

  switch(state){

  case 1:

    led_init(0);//LED off
    song1();//plays song1
    clearScreen(COLOR_BLUE);//used to make the screen blue
    triangleDown(centerX,centerY,size,COLOR_YELLOW);//draws a triangle facing down
  

    break;

  case 2://led on, play song2, background black, draw triangle facing up
    led_init(1);
    song2();
    clearScreen(COLOR_BLACK);
    triangleUp(centerX,centerY,size,COLOR_RED);
    

    break;

  case 3://led on, play song3, backgound red, draw triangle facing left

    led_init(0);
    song3();
    clearScreen(COLOR_RED);
    triangleLeft(centerX,centerY,size,COLOR_BLUE);


    break;

  case 4:
    led_init(1);
    song4();
    clearScreen(COLOR_BROWN);
    triangleRight(centerX,centerY,size,COLOR_GREEN);

    break;

  default:
    clearScreen(COLOR_WHITE);
    led_init(0);

   
    break;

  }




}
