#include "neslib.h"
#include <stdio.h> 
#include <stdlib.h>
#include <nes.h>
#include <string.h>
#define TILE 0xc4 //cup
#define TILE2 0xc8 //ball
#define TILE3 0x1f//arrow
#define TILE4 0x00//empty
#define ATTR 0
#define NUM_ACTORS 4

// link the pattern table into CHR ROM
//#link "chr_generic.s"
// main function, run after console reset

  const unsigned char metasprite[]={
        0,      0,      TILE+0,   ATTR, 
        0,      8,      TILE+1,   ATTR, 
        8,      0,      TILE+2,   ATTR, 
        8,      8,      TILE+3,   ATTR, 
        128};
  
  const unsigned char metasprite2[]={
        0,      0,      TILE2+0,   ATTR, 
        0,      8,      TILE2+1,   ATTR, 
        8,      0,      TILE2+2,   ATTR, 
        8,      8,      TILE2+3,   ATTR, 
        128};
  const unsigned char metasprite3[]={
        0,      0,      TILE3,   ATTR,
        //0,      0,      TILE4,   ATTR,
       // 0,      0,      TILE4,   ATTR,
       // 0,      0,      TILE4,   ATTR,
        128};
  const char PALETTE[32] = { 
  0x05,			// screen color

  0x11,0x30,0x27,0x0,	// background palette 0
  0x1c,0x20,0x2c,0x0,	// background palette 1
  0x00,0x10,0x20,0x0,	// background palette 2
  0x06,0x16,0x26,0x0,	// background palette 3

  0x16,0x35,0x24,0x0,	// sprite palette 0
  0x00,0x37,0x25,0x0,	// sprite palette 1
  0x0d,0x2d,0x3a,0x0,	// sprite palette 2
  0x0d,0x27,0x2a	// sprite palette 3
  };

  byte actor_x[NUM_ACTORS];
  byte actor_y[NUM_ACTORS];
  // actor x/y deltas per frame (signed)
  sbyte actor_dx[NUM_ACTORS];
  sbyte actor_dy[NUM_ACTORS];

void setup_graphics() 
{
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
  // turn on PPU
  ppu_on_all();
}

void title_screen() 
{
  vram_adr(NTADR_A(12,2));	
  vram_write("Welcome", 7);
  
  vram_adr(NTADR_A(6,22));	
  vram_write("Press start to begin", 20);
  
  ppu_on_all();

 while(1)
  {
    if(pad_trigger(0)&PAD_START) break;    
  }
}

void display_cups()
{
  int i;
  char oam_id;
  setup_graphics();
 
  actor_x[0]=20;
  actor_y[0]=80;
  actor_x[1]=40;
  actor_y[1]=180; 
  actor_x[2]=100;
  actor_y[2]=180;
  actor_x[3]=160;
  actor_y[3]=180;
  
  oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite3);
  for(i=1;i<NUM_ACTORS;i++)
  {
   oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, metasprite);
  }
}

void shuffle()
{
  char oam_id;
  int j;
  int i;
  
  for(i=0;i<4;i++)
  {
  for(j=0;j<12;j++)
    {
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite3);
      oam_id = oam_meta_spr(actor_x[1], actor_y[1], oam_id, metasprite);
      actor_x[1] += 5;
      oam_id = oam_meta_spr(actor_x[2], actor_y[2], oam_id, metasprite);
      oam_id = oam_meta_spr(actor_x[3], actor_y[3], oam_id, metasprite);
      actor_x[3] -= 5;
      ppu_wait_frame();
      oam_clear();
    }
      for(j=0;j<15;j++)
    {
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite3);
      oam_id = oam_meta_spr(actor_x[1], actor_y[1], oam_id, metasprite);
      actor_x[1] -= 4;
      oam_id = oam_meta_spr(actor_x[2], actor_y[2], oam_id, metasprite);
      oam_id = oam_meta_spr(actor_x[3], actor_y[3], oam_id, metasprite);
      actor_x[3] += 4;
      ppu_wait_frame();
      oam_clear();
    }
    
  } 
}

void display_ball(int x)
{
  int i;
  char oam_id;
  setup_graphics();
 
  oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite3);
  for(i=1;i<4;i++)
  {
    if(i==x)
    {
      continue;   
    }
    oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, metasprite);
    oam_id = oam_meta_spr(actor_x[x], actor_y[x], oam_id, metasprite2);
  }
  
  for(i=0;i<75;i++)
  {
    ppu_wait_frame();
  }
}

void guess(int seed)
{
  int num = ((seed+rand()) % 3) +1; //winning cup number
  int score;
  int i;
  int cup=1;  //user selected cup number
  char oam_id;
  char scr[]="";
  char str[] ="";
  sprintf(str, "%d", num); 
  
  display_cups();
  
  while(1)
  {
    if(pad_trigger(0)&PAD_DOWN && (actor_y[0] >=80 && actor_y[0] < 110))
    {
      oam_clear();
      cup++;
      actor_y[0]+=15;
      
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite3);
      for(i=1;i<NUM_ACTORS;i++)
      {
        oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, metasprite);
      }
    }  
    
    if(pad_trigger(0)&PAD_UP && (actor_y[0] >80 && actor_y[0] <= 110))
    {
      oam_clear();
      actor_y[0]-=15;
        
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite3);
      for(i=1;i<NUM_ACTORS;i++)
      {
       oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, metasprite);
      } 
    }
    
    if(pad_trigger(0)&PAD_START)
    {
      shuffle();
      if(cup==num)
      {
        ppu_off();
        
        score=score+1;
        vram_adr(NTADR_A(6,18)); 	
        vram_write("WIN!", 4);
       
        vram_adr(NTADR_A(19,19)); 
        vram_write(str,1);
        vram_adr(NTADR_A(6,19)); 	
        vram_write("Winning cup:", 12);
  
        sprintf(scr,"%d",score);
        vram_adr(NTADR_A(13,20)); 
        vram_write(scr,2);
        vram_adr(NTADR_A(6,20)); 	
        vram_write("SCORE:", 6);
        
        ppu_on_all();  
        display_ball(num);
        break;
      }
    else
    {
      ppu_off();
      vram_adr(NTADR_A(6,18)); 	
      vram_write("LOSE", 4);

      vram_adr(NTADR_A(19,19)); 
      vram_write(str,1);
      vram_adr(NTADR_A(6,19)); 	
      vram_write("Winning cup:", 12);
         
      sprintf(scr,"%d",score);
      vram_adr(NTADR_A(13,20)); 
      vram_write(scr,2);
      vram_adr(NTADR_A(6,20)); 	
      vram_write("SCORE:", 6);
      ppu_on_all();
      display_ball(num);

      break;
     }
    }    
  }
}

void game(int seed)
{

  char str[] =""; //score to char string 
  ppu_off();
  
  vram_adr(NTADR_A(8,2));		// set address
  vram_write("CUP GUESSING GAME!", 17);// write bytes to video RAM
 
  vram_adr(NTADR_A(2,6));
  vram_write("Please choose a cup using \x1c\x1d",28);
  
  vram_adr(NTADR_A(2,7));
  vram_write("then press 'start'",18);
  
  vram_adr(NTADR_A(6,10));
  vram_write("Cup 1",5);
  
  vram_adr(NTADR_A(6,12));
  vram_write("Cup 2",5);
  
  vram_adr(NTADR_A(6,14));
  vram_write("Cup 3",5);
  
  vram_adr(NTADR_A(6,22));	
  vram_write("                   ", 20);

  ppu_on_all();
  
  guess(seed);
  
}

void main(void) {
  int seed;

  // set palette colors
  pal_col(0,0x05);	// set screen to red
  pal_col(1,0x01);	// fuchsia
  //pal_col(2,0x20);	// grey
  pal_col(3,0x29);	// white
  
  title_screen();
  

  while (1) 
  {   
     seed = (rand() % 100);
     game(seed); 
           
  }   
}


