/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <math.h>
#include "game.h"    /* Declatations for these labs */

volatile int *portE = (volatile int *)0xbf886110;
#define SPAWN_POINT_X 20 // Starting value x
#define SPAWN_POINT_Y 8  // Starting value Y

// initiation of all variables
int timeoutcount = 0;
int trackNr = 1;
int trainPosX = SPAWN_POINT_X;
int trainPosY = SPAWN_POINT_Y;
int enemyPosX = 110;
int enemyPosY = 8;
int scorePosX = 110;
int scorePosY = 22;
int collisionPoint = SPAWN_POINT_X + 6;
int score;
int difficulty = 100;

// Interrupt Service for track switching
void user_isr(void)
{
  if (IFS(0) & 0x100)
  {
    IFS(0) & 0xfffffeff;

    timeoutcount++;
  }
}

// initialisation of the ports and timers directly copied from lab3 of IS1200 written by Victor Karlström 2023
void game_init(void)
{
  volatile int *E = (volatile int *)0xbf886100;
  *E = *E & 0xffffff00;
  // Clock
  //  and btn 2-4 (D 0xe0)
  TRISDSET = 0b111111100000;
  /*TMR2 = 1;
  PR2 = 31250;
  T2CON = 0x8070;*/

  T3CONSET = 0x8000;
  // btn 1
  TRISFSET = 0b10;

  // Initialization of interrupts
  // bit 8 (Enable)
  IEC(0) = 0x100;
  // bit 4:2 (Priority) och 1:0 (Subpriority)
  IPC(2) = 0x10;


  // Call function in labwork.S to enable interrupts globally
  enable_interrupt();

  return;
}
/* This function is called repetitively from the main program */
void track_switch()
{
  int switches = getsw();

  if (switches == 1)
  {
    trainPosY = 8;
    trackNr = 1;
  }
  else
  {
    trainPosY = 22;
    trackNr = 2;
  }
}

void entity_logic()
{
  enemyPosX--;
  if (enemyPosX < 4)
  {
    enemyPosX = 128;
  }
  scorePosX--;
  if (scorePosX < 4)
  {
    randomTrack();
    scorePosX = 128;
  }

  if ((trackNr == 1) && (scorePosY == 8))
  {
    if (scorePosX == collisionPoint)
    {
      score++;
      difficulty = 100 - (score * 15);
    }
  }

  if ((trackNr == 1) && (enemyPosY == 8))
  {
    if (enemyPosX == collisionPoint)
    {
      gameStatus = 0;
    }
  }
  if ((trackNr == 2) && (scorePosY == 20))
  {
    if (scorePosX == collisionPoint)
    {
      score++;
      difficulty = 100 - (score * 15);
    }
  }

  if ((trackNr == 2) && (enemyPosY == 20))
  {
    if (enemyPosX == collisionPoint)
    {
      gameStatus = 0;
    }
  }
}

void randomTrack(){
  int i = TMR3;
  if(i % 2 == 1){
    scorePosY = 8;
    enemyPosY = 20;
  }
  else{
    scorePosY = 20;
    enemyPosY = 8;
  }
}

void draw()
{
  int i, j;

  front_cart(trainPosY, trainPosX);
  back_cart(trainPosY, trainPosX - 6);
  barn(scorePosY, scorePosX);
  mommy(enemyPosY, enemyPosX);

  for (i = 1; i < 4; i++)
  {
    for (j = 0; j < 128; j++)
    {
      displayPixels[i][j] = 1;
    }
  }

  for (i = 15; i < 18; i++)
  {
    for (j = 0; j < 128; j++)
    {
      displayPixels[i][j] = 1;
    }
  }

  for (i = 29; i > 28; i++)
  {
    for (j = 0; j < 128; j++)
    {
      displayPixels[i][j] = 1;
    }
  }
}

void game_loop(void)
{
  display_clear();

  track_switch();
  delay(difficulty);
  entity_logic();
  draw();

  draw_pixel();
}
