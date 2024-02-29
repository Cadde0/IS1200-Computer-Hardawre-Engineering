/* mipslab.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
void draw_pixel(void);
int check_collision(int trainY, int objectY, int objectX);
void lose_screen(void);
void barn(int y, int x);
void mommy(int y, int x);
void front_cart(int y, int x);
void back_cart(int y, int x);

void display_clear(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char *itoaconv(int num);
void game_loop(void);
int nextprime(int inval);
void quicksleep(int cyc);
void tick(unsigned int *timep);

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug(volatile int *const addr);

extern uint8_t displayPixels[32][128];

/* Declare bitmap array containing font */
extern const uint8_t const font[128 * 8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

extern const uint8_t const train[32][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string(char *, int);
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void track_switch(void);
void enable_interrupt(void);
//void randomTrack(void);

int gameStatus;
int score;
int collisionpoint;
