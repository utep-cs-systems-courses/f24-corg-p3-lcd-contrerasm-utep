#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"



#define LED BIT6
#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SWITCHES 15



// Notes for the jingle

#define NOTE_C 261.63
#define NOTE_E 329.63
#define NOTE_G 392.00



// Global variables

int switches = 0;
short redrawScreen = 1;
unsigned char ballColorToggle = 0;
unsigned int trunkColor = COLOR_BROWN;



// Ball positions and movement

short ball1Pos[2] = {screenWidth/2,screenHeight-50};
short ball2Pos[2] = {screenWidth/2,screenHeight-70};

short ball1Control[2] = {screenWidth/2,screenHeight-50};
short ball2Control[2] = {screenWidth/2,screenHeight-70};
short velocity1 = 1;
short velocity2 = -1;

// Jingle state
unsigned char noteIndex = 0;
const float notes[] = {NOTE_C, NOTE_E, NOTE_G};
const int totalNotes = 3;
unsigned char playingJingle = 0;
unsigned char noteTimer = 0;


void triangleUp(int startX, int startY, int size, unsigned int color) {
  for (int y = 0; y < size; y++) {
    int halfWidth = size-y-1;
    for (int x = startX - halfWidth; x <= startX + halfWidth; x++) {
      fillRectangle(x, startY - y, 1, 1, color);
    }
  }
}

void draw_star(int centerX, int centerY, unsigned int color) {
  fillRectangle(centerX-2, centerY, 5, 1, color);
  fillRectangle(centerX, centerY-2, 1, 5, color);
  fillRectangle(centerX-1, centerY-1, 3, 3, color);
}

void draw_ball(int col, int row, unsigned short color) {

  fillRectangle(col-1, row-1, 3, 3, color);

}

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
void update_ball_positions() {

  //update first ball, lower one
  ball1Control[0] += velocity1;
  if(ball1Control[0] <= screenWidth/2 - 30 || ball1Control[0] >= screenWidth/2 + 30) {
    velocity1 = -velocity1;
  }

  //update second ball, more towards center
  ball2Control[0] += velocity2;
  if(ball2Control[0] <= screenWidth/2 - 15 || ball2Control[0] >= screenWidth/2 + 15) {
    velocity2 = -velocity2;
  }

}

void draw_balls() {

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

void buzzer_init() {

  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;

}

void buzzer_set_period(short cycles){
  CCR0=cycles;
  CCR1=cycles>>1;
}

static char switch_update_interrupt_sense() {

  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;

}

void switch_init() {

  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();

}

void switch_interrupt_handler() {

  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;

}

void wdt_c_handler() {

  static int secCount = 0;
  secCount++;

  if (secCount >= 25) {  // 10/sec
    secCount = 0;



    // Toggle ball colors every second

    static int colorCount = 0;
    colorCount++;
    if(colorCount >= 10) {
      colorCount = 0;
      ballColorToggle = !ballColorToggle;

    }



    // Update ball positions

    update_ball_positions();
    // Handle jingle for SW2

    if(switches & SW2) {
      drawString5x7(screenWidth/2 -40,20,"Happy Holidays",COLOR_WHITE,COLOR_BLACK);
      if(!playingJingle) {

	playingJingle = 1;
	noteIndex = 0;
	noteTimer = 0;
	
      }

    }
    if(playingJingle) {

      noteTimer++;
      if(noteTimer >= 20) {  // 2 seconds between notes
	noteTimer = 0;
	if(noteIndex < totalNotes) {

	  int period = 2000000 / notes[noteIndex];

	  buzzer_set_period(period);
	  noteIndex++;
	} else {
	  playingJingle = 0;
	  buzzer_set_period(0);
	  drawString5x7(screenWidth/2-40,20,"Happy Holidays",COLOR_BLACK,COLOR_BLACK);

	}

      }

    }



    // Update trunk color if SW3 is pressed

    if(switches & SW3) {
      trunkColor = COLOR_BLACK;  // Or any other color change logic
    } else {

      trunkColor = COLOR_BROWN;

    }



    if(switches & SW4) return;
    redrawScreen = 1;

  }

}
void update_shape();
void main() {
  P1DIR |= LED;
  P1OUT |= LED;



  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();

  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_BLACK);

  while(1) {

    if(redrawScreen) {
      redrawScreen = 0;
      update_shape();
    }

    P1OUT &= ~LED;
    or_sr(0x10);
    P1OUT |= LED;
  }

}
void update_shape(){
  draw_tree();
  draw_balls();
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {

  if(P2IFG & SWITCHES) {
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}