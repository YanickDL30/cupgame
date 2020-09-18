#include "neslib.h"
#include <stdio.h> 
#include <stdlib.h>

// link the pattern table into CHR ROM
//#link "chr_generic.s"

// main function, run after console reset


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
  
  // set palette colors
  pal_col(0,0x05);	// set screen to red
  pal_col(1,0x01);	// fuchsia
  //pal_col(2,0x20);	// grey
  pal_col(3,0x29);	// white
  
  title_screen();
 
 

  
  // write text to name table
  // infinite loop
  while (1) 
  {  
    
     game();
    
    
  } 
     
}

