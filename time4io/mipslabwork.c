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

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int * tris_e = (volatile int *) 0xbf886100;
  * tris_e = * tris_e & (0xFF00); //8 least significant bits of Trise set 0
  TRISD = TRISD & 0x0fe0;
  volatile int* port_e = (volatile int *) 0xbf886110;
  * port_e = 0x0;
  return
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  int switches = getsw();
  int buttons = getbtns();
  //for button 2
  if(buttons & 1 ){
    mytime = (switches << 4) | (mytime & 0xFF0F);
  }
  // for button 3
  if(buttons & 2 ){
    mytime = (switches << 8) | (mytime & 0xF0FF);
  }
  // for button 4
  if(buttons & 4){
    mytime = (switches << 12) | (mytime & 0x0FFF);
  }
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
  *port_e += 1;
}
