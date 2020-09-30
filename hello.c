#include "neslib.h"
#include <stdio.h> 
#include <stdlib.h>
#include <nes.h>
#include <string.h>
#define TILE 0xc4
#define ATTR 0
#define NUM_ACTORS 3


// link the pattern table into CHR ROM
//#link "chr_generic.s"

// main function, run after console reset

  const unsigned char metasprite[]={
        0,      0,      TILE+0,   ATTR, 
        0,      8,      TILE+1,   ATTR, 
        8,      0,      TILE+2,   ATTR, 
        8,      8,      TILE+3,   ATTR, 
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

void guess()
{
  int num = (rand() % 3) +1;
  int score;
 
  char scr[]="";
  char str[] ="";
  sprintf(str, "%d", num); 
  
  while(1)
  {
    if(pad_trigger(0)&PAD_A)
    {
      if(num==1)
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

      break;
     }
    }
    
    if(pad_trigger(0)&PAD_B)
    {
      if(num==2)
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
       break;
     }
    }
    
    if(pad_trigger(0)&PAD_SELECT)
    {
      if(num==3)
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
        vram_write(scr,1);
        vram_adr(NTADR_A(6,20)); 	
        vram_write("SCORE:", 6);
        ppu_on_all();
        break;
      }
      else
      {
        ppu_off();
        vram_adr(NTADR_A(6,18)); 	
        vram_write("LOSE", 4);
        
        vram_adr(NTADR_A(19,19)); 
        vram_write(str,2);
        vram_adr(NTADR_A(6,19)); 	
        vram_write("Winning cup:", 12);
        
        
        sprintf(scr,"%d",score);
        vram_adr(NTADR_A(13,20)); 
        vram_write(scr,2);
        vram_adr(NTADR_A(6,20)); 	
        vram_write("SCORE:", 6);
        ppu_on_all();

        break;
      }
    }
  } 
  
}

void game()
{

  char str[] =""; //score to char string
  ppu_off();

  vram_adr(NTADR_A(8,2));		// set address
  vram_write("CUP GUESSING GAME!", 17);// write bytes to video RAM
 
  vram_adr(NTADR_A(2,6));
  vram_write("Please choose a cup:",20);
  
  vram_adr(NTADR_A(2,10));
  vram_write("\x1f Cup 1 (a)",11);
  
  vram_adr(NTADR_A(2,12));
  //vram_write("Cup 2 (b)",9);
  vram_write("\x1f Cup 2 (b)",11);
  
  vram_adr(NTADR_A(2,14));
  vram_write("\x1f Cup 3 (select)",16);
  
  vram_adr(NTADR_A(6,22));	
  vram_write("                   ", 20);

  ppu_on_all();
  
  guess();
  
}

void main(void) {
  char oam_id;
  int i;
  int j;
  
  // set palette colors
  pal_col(0,0x05);	// set screen to red
  pal_col(1,0x01);	// fuchsia
  //pal_col(2,0x20);	// grey
  pal_col(3,0x29);	// white
  
  title_screen();
  setup_graphics();
 
  actor_x[0]=40;
  actor_y[0]=180;
  actor_dx[0]=2;
  
  actor_x[1]=100;
  actor_y[1]=180;

  actor_x[2]=160;
  actor_y[2]=180;

  for(i=0;i<NUM_ACTORS;i++)
  {
   oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, metasprite);
  }

  while (1) 
  {   
    game();    
      
    //shuffle right
    for(j=0;j<1000;j++)
    {
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite);
      actor_x[0] += actor_dx[0];
    }
    //shuffle left
    for(j=0;j<1000;j++)
    {
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite);
      actor_x[0] -= actor_dx[0];
    }
    //shuffle right again
    for(j=0;j<1000;j++)
    {
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite);
      actor_x[0] += actor_dx[0];
    }
    //shuffle left again
    for(j=0;j<1000;j++)
    {
      oam_id = oam_meta_spr(actor_x[0], actor_y[0], oam_id, metasprite);
      actor_x[0] -= actor_dx[0];
    }
    
    oam_clear();
  
    actor_x[0]=40;
    actor_y[0]=180;
    actor_x[1]=100;
    actor_y[1]=180;
    actor_x[2]=160;
    actor_y[2]=180;
    for(i=0;i<NUM_ACTORS;i++)
    {
     oam_id = oam_meta_spr(actor_x[i], actor_y[i], oam_id, metasprite);
    } 
    
  }   
}

