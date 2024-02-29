/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
int timeoutcount = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * trise = (volatile int *) 0xbf886100;
  * trise = * trise & (0xFF00); //8 least significant bits of Trise set 0
  TRISD = TRISD & 0x0fe0;

  T2CON = 0x70;
  PR2 = ((80000000 / 256) / 10);
  TMR2 = 0;
  T2CON = 0x8000;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int* porte = (volatile int *) 0xbf886110;
  * porte = 0x0;

  int count = 0x0;
  int i;
  int j;
  while(1){
    
    if (IFS(0) & 0x100)
    {
      IFS(0) = 0x0;  //Reset the flag at 100ms
      timeoutcount++;
      if (timeoutcount == 10)
      {
        timeoutcount = 0;
        time2string( textstring, mytime );
        display_string( 3, textstring );
        display_update();
        tick( &mytime );
      }
    }
    
    i = getsw();
    j = getbtns();
    //button 2
    if(j & 1 ){
      mytime = (i << 4) | (mytime & 0xFF0F);
    }
    //button 3
    if(j & 2 ){
      mytime = (i << 8) | (mytime & 0xF0FF);
    }
    //button 4
    if(j & 4){
      mytime = (i << 12) | (mytime & 0x0FFF);
    }
    
    //delay( 1000 );

    count ++;
    display_image(96, icon);
    * porte = count;
  }
}
