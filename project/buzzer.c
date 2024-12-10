#include <msp430.h>

#include "libTimer.h"

#include "buzzer.h"


void buzzer_init()

{

  /*Diret timer A output "TA0.1 to P2.6.

    According to table 21 from data sheet:

    P2SEL2.6, P2SEL2.7, and P2SEL.7 must be zero

    P2SEL.6 must be 1

    Also: P2.6 direction must be output */

  timerAUpmode(); /*used to drive speaker*/
  P2SEL2 &= ~(BIT6 |BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; /*enable output to speaker (p2.6)*/

}//end of buzzer_inti



void buzzer_set_period(short cycles) //We use this to change the sound the buzzer makes.

{
  CCR0=cycles;
  CCR1=cycles>>1;

}//end of buzzer_set_period



void buzzer_off(){//we set CCR0 and CCR1 to 0 to turn off the buzzer

  CCR0=0;
  CCR1=0;

}//end of buzzer off



void song1()

{

  int jingle[] = {C5, E5, G5, E5, C5, E5, G5, E5, A4, C5, E5, C5, A4, A4, C5, A4};
  int totalNotes =sizeof(jingle)/sizeof(jingle[0]);
  for(int i=0; i<totalNotes;i++){

    buzzer_set_period(jingle[i]);//play note
    __delay_cycles(2000000);//hold note
    buzzer_set_period(0);//stop the note
    __delay_cycles(2000000);//used to create a short pause between notes
  }

  buzzer_set_period(0);//this is used to make sure the buzzer turns off

}//end of mcdonalds
void song2()

{
  int jingle[] = {C5, G5, G5,0 , C5, E5, 0, 0, A4, C5, 0, C5, 0, A4, 0,A4};
  int totalNotes =sizeof(jingle)/sizeof(jingle[0]);
  for(int i=0; i<totalNotes;i++){

    buzzer_set_period(jingle[i]);//play note
    __delay_cycles(2000000);//hold note
    buzzer_set_period(0);//stop the note
    __delay_cycles(2000000);//used to create a short pause between notes
  }
  buzzer_set_period(0);//this is used to make sure the buzzer turns off

}//end of song2

void song3()

{

  int jingle[] = {C5, C5, C5, E5, E5, E5, E5, E5, A4, A4, A4, C5, C5, A4, C5,A4};
  int totalNotes =sizeof(jingle)/sizeof(jingle[0]);
  for(int i=0; i<totalNotes;i++){
    buzzer_set_period(jingle[i]);//play note
    __delay_cycles(2000000);//hold note
    buzzer_set_period(0);//stop the note
    __delay_cycles(2000000);//used to create a short pause between notes
  }
  buzzer_set_period(0);//this is used to make sure the buzzer turns off

}//end of song3

void song4()
{

  int jingle[] = {0, 0, 0, E5, 0, E5, 0, E5, 0, 0, E5, 0, 0, A4, 0,A4};



  int totalNotes =sizeof(jingle)/sizeof(jingle[0]);



  for(int i=0; i<totalNotes;i++){
    buzzer_set_period(jingle[i]);//play note
    __delay_cycles(2000000);//hold note
    buzzer_set_period(0);//stop the note
    __delay_cycles(2000000);//used to create a short pause between notes
  }
  buzzer_set_period(0);//this is used to make sure the buzzer turns off

}//end of song4
