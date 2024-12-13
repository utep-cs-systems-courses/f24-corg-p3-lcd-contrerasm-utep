#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"


//used for the 4 swithces
#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SWITCHES 15




//used for the jinle on switch 2
#define NOTE_C 261.63
#define NOTE_E 329.63
#define NOTE_G 392.00


int switches = 0;//used to store current switch state
short redrawScreen = 1;//used to update screen
unsigned int trunkColor  = COLOR_BROWN;

//used for the balls position, target position and color and speed
unsigned char ballColorToggle =0;
short ball1Pos[2] = {screenWidth/2,screenHeight-50};
short ball2Pos[2] = {screenWidth/2,screenHeight-70};
short ball1Control[2] = {screenWidth/2,screenHeight-50};
short ball2Control[2] = {screenWidth/2,screenHeight-70};
short velocity1 = 2;
short velocity2 = -2;


unsigned char noteIndex = 0;//used to track current note
const float notes[] = {NOTE_C, NOTE_E, NOTE_G};//an array of notes
const int totalNotes = 3;//size of note
unsigned char playingJingle = 0;//used to track if the jingle is playing
unsigned char noteTimer = 0;//used for note duration

//used to draw the top of tree
void triangleUp(int startX, int startY, int size, unsigned int color) {
  for (int y = 0; y < size; y++) {
    int halfWidth = size-y-1;
    for (int x = startX - halfWidth; x <= startX + halfWidth; x++) {
      fillRectangle(x, startY - y, 1, 1, color);
    }
  }
}
//used to draw star for switch1
void draw_star(int centerX, int centerY, unsigned int color) {
  fillRectangle(centerX-2, centerY, 5, 1, color);
  fillRectangle(centerX, centerY-2, 1, 5, color);
  fillRectangle(centerX-1, centerY-1, 3, 3, color);
}

//used to draw balls used in the idel state
void draw_ball(int col, int row, unsigned short color) {

  fillRectangle(col-1, row-1, 3, 3, color);

}
//used to draw tree, holds switch statement to keep star visible
void draw_tree() {
  //draw trunk for tree
  int trunkWidth = 20;
  int trunkHeight = 30;
  int trunkX = screenWidth/2 - trunkWidth/2;
  int trunkY = screenHeight - trunkHeight;

  fillRectangle(trunkX, trunkY, trunkWidth, trunkHeight, trunkColor);



  //draw tree top for tree
  triangleUp(screenWidth/2, trunkY, 60, COLOR_GREEN);



  // Draw star and text if SW1 is pressed
  if(switches & SW1) {
    draw_star(screenWidth/2, trunkY - 65, COLOR_YELLOW);
    drawString5x7(screenWidth/2 - 30, 40, "MERRY XMAS", COLOR_WHITE,COLOR_BLACK);
  }



  

}
//
void update_ball_positions() {
  //update first ball, lower one
  ball1Control[0] += velocity1;
  
  if(ball1Control[0] <= screenWidth/2 - 30 || ball1Control[0] >= screenWidth/2 + 30) {
    velocity1 = -velocity1;//used to reverse once it hits boundries of tree
  }

  //update second ball, more towards center
  ball2Control[0] += velocity2;
  
  if(ball2Control[0] <= screenWidth/2 - 15 || ball2Control[0] >= screenWidth/2 + 15) {
    velocity2 = -velocity2;//uses to reverse
  }

}

void draw_balls() {
  //used to decide ball color
  unsigned int ballColor = ballColorToggle ? COLOR_WHITE : COLOR_GREEN;
  //color old positions
  draw_ball(ball1Pos[0], ball1Pos[1], COLOR_GREEN);
  draw_ball(ball2Pos[0], ball2Pos[1], COLOR_GREEN);

  //update ball position
  ball1Pos[0] = ball1Control[0];
  ball2Pos[0] = ball2Control[0];

  //draw new position
  draw_ball(ball1Pos[0], ball1Pos[1], ballColor);
  draw_ball(ball2Pos[0], ball2Pos[1], ballColor);

}
//used for the buzzer, for the jingle
void buzzer_init() {
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;//timer function
  P2DIR = BIT6;//output
}

//used for the buzzer sound frequency
void buzzer_set_period(short cycles){
  CCR0=cycles;
  CCR1=cycles>>1;
}

//used to prevent missing switch changes
static char switch_update_interrupt_sense() {
  char p2val = P2IN;//reads p2 values
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;

}

void switch_init() {
  P2REN |= SWITCHES;//enables resistors
  P2IE |= SWITCHES;//interupts enables
  P2OUT |= SWITCHES;//pull ups for switches
  P2DIR &= ~SWITCHES;//used to set swithces for input
  switch_update_interrupt_sense();

}

void switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;//update the global switch state
}

void wdt_c_handler() {//keeps the party going

  static int secCount = 0;
  secCount++;
  
  if (secCount >=120){//controls timining interval 
    secCount = 0;
    

    //following code is used for the ball color in the idle state
    static int colorCount = 0;
    colorCount++;
    if(colorCount >= 5) {
      colorCount = 0;
      ballColorToggle = !ballColorToggle;
    }

    
    
    //if switch 2 is pressed, display and play jingle
    if(switches & SW2) {
      drawString5x7(screenWidth/2 -40,20,"Happy Holidays",COLOR_WHITE,COLOR_BLACK);
      if(!playingJingle) {//used to set up the jingle, if not started start

	playingJingle = 1;
	noteIndex = 0;
	noteTimer = 0;
      }

    }//end of sw2 pressed
    
    if(playingJingle) {//following is 

      noteTimer++;
      if(noteTimer >= 3 ) {//used to decide when to change notes
	noteTimer = 0;
	if(noteIndex < totalNotes) {
	  int period = 2000000 / notes[noteIndex];//used to convert the note to period

	  buzzer_set_period(period);//play note
	  noteIndex++;
	 
	} else {
	  playingJingle = 0;//stop playing jingle
	  buzzer_set_period(0);
	  drawString5x7(screenWidth/2-40,20,"Happy Holidays",COLOR_BLACK,COLOR_BLACK);//clear text

	}

      }

    }


    //used in sw3 to change the color of the trunk to white, while held
    if(switches & SW3) {
      trunkColor =COLOR_WHITE;
    } else{
      trunkColor=COLOR_BROWN;
    }//end of sw3
   
    //switch 4, just a pause
    if(switches & SW4) return;
    redrawScreen = 1;//update screen

  }//end of sec count
  
}//end of watch dog

void update_shape();

void main() {
  
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  led_init(0);

  enableWDTInterrupts();
  or_sr(0x8);//enable interrupts

  clearScreen(COLOR_BLACK);

  while(1) {

    if(redrawScreen) {//if it needs to update
      redrawScreen = 0;
      update_shape();
    }

    led_init(0);//led off
    or_sr(0x10);//cpu off
    led_init(1);//led on
  }

}

void update_shape(){
  update_ball_positions();//update ball location
  draw_tree();//draw tree
  draw_balls();//draw balls
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {

  if(P2IFG & SWITCHES) {//did a button cause this interrupt?
    P2IFG &= ~SWITCHES;//clear pending sw interrupts
    switch_interrupt_handler();//single handler for all interrupts
  }
}
