
#include "SDL.h"
#define vit 50
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define Sleep(n) usleep(n)
#define pusize_haut 100
#define pusize_larg 90

SDL_TimerID timer;
double sprx,spry ;
int forward,kicks,uppercut,croush,jum,ri,le,frames=0;

SDL_Rect ap1 , rcsprite ,left,rcleft,right,rcright,rcfor,forw[3],forwr[3],upperr[2],upper[2],rcupper,kick[2],rckick,jump,rcjump,bas,rcbas,rcupperr,rckickr,kickr[2],rcforr,rightr,rcrightr,leftr,rcleftr,basr,rcbasr,apr,rcspriter;
struct personnage 
{
  int pdv;
  int right;//direction du personnage
  int left;
}pers;



struct enemis
{
	int pdv;
};



void setforward()
{
  forw[0].x = 0;
  forw[0].y = 0;
  forw[0].h = pusize_haut;
  forw[0].w =  90;
  forw[1].x = 99;
  forw[1].y = 0;
  forw[1].h = pusize_haut;
  forw[1].w =  50;
  forw[2].x = 157;
  forw[2].y = 0;
  forw[2].h = pusize_haut;
  forw[2].w =  80;
}
void setforwardr()
{
  forwr[0].x = 927;
  forwr[0].y = 0;
  forwr[0].h = pusize_haut;
  forwr[0].w =  90;
  forwr[1].x = 870;
  forwr[1].y = 0;
  forwr[1].h = pusize_haut;
  forwr[1].w =  50;
  forwr[2].x =  792;
  forwr[2].y = 0;
  forwr[2].h = pusize_haut;
  forwr[2].w =  80;
}
void setkick()
{
  kick[0].x = 0;
  kick[0].y = 0;
  kick[0].h = 100 ;
  kick[0].w = 70;
  kick[1].x = 80;
  kick[1].y = 0;
  kick[1].h = 100;
  kick[1].w = 80;
}
void setkickr()
{
  kickr[0].x = 950;
  kickr[0].y = 0;
  kickr[0].h = 100 ;
  kickr[0].w = 70;
  kickr[1].x = 854;
  kickr[1].y = 0;
  kickr[1].h = 100;
  kickr[1].w = 80;
}

void setupper()
{
  upper[0].x = 0;
  upper[0].y = 0;
  upper[0].h = 100 ;
  upper[0].w = 90;
  upper[1].x = 80;
  upper[1].y = 0;
  upper[1].h = 100;
  upper[1].w = 93;
}
void setupperr()
{
  upperr[0].x = 930;
  upperr[0].y = 0;
  upperr[0].h = 100 ;
  upperr[0].w = 90;
  upperr[1].x = 859;
  upperr[1].y = 0;
  upperr[1].h = 100;
  upperr[1].w = 70;
}


  
int main ( int argc, char *argv[] )
{
  SDL_Surface *sprite , *temp , *screen, *pow, *mov0,*mov1,*mov2,*mov3,*mov4,*mov5,*mov6, *movr0,*movr1,*movr2,*movr3,*movr4,*movr5,*movr6,*spriter;
  int colorkey;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("fail fighter", "fail fighter");

  /* create window */
  screen = SDL_SetVideoMode(1047, 480, 0, 0);
  
  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255 , 255 , 255);
  /* load bitmap to temp surface */
  temp = SDL_LoadBMP("mission1.bmp");
  SDL_Surface* bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
	
  /* load sprite */
  temp   = SDL_LoadBMP("perso/static.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /* character movements*/
  temp   = SDL_LoadBMP("perso/jump.bmp");
  mov0  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov0, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // avancer
  temp   = SDL_LoadBMP("perso/avancer.bmp");
  mov1  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // kick
  temp   = SDL_LoadBMP("perso/kick.bmp");
  mov2  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // left
  temp   = SDL_LoadBMP("perso/left.bmp");
  mov3  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // right
  temp   = SDL_LoadBMP("perso/right.bmp");
  mov4  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov4, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // uppercut
  temp   = SDL_LoadBMP("perso/uppercut.bmp");
  mov5  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov5, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // crouch
  temp   = SDL_LoadBMP("perso/bas.bmp");
  mov6  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov6, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
   /* load sprite */
  temp   = SDL_LoadBMP("perso/staticr.bmp");
  spriter = SDL_DisplayFormat(temp);
  SDL_SetColorKey(spriter, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /* character movements reverse*/
  temp   = SDL_LoadBMP("perso/jump.bmp");
  movr0  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr0, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // avancer reverse 
  temp   = SDL_LoadBMP("perso/avancerr.bmp");
  movr1  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // kick reverse 
  temp   = SDL_LoadBMP("perso/kickr.bmp");
  movr2  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // left reverse 
  temp   = SDL_LoadBMP("perso/leftr.bmp");
  movr3  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // right reverse
  temp   = SDL_LoadBMP("perso/rightr.bmp");
  movr4  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr4, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // uppercut reverse
  temp   = SDL_LoadBMP("perso/uppercutr.bmp");
  movr5  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr5, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // crouch reverse
  temp   = SDL_LoadBMP("perso/basr.bmp");
  movr6  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr6, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /*charcater position*/
 
  rcsprite.x = 150 ;	
  rcsprite.y = 300 ;
  rckick.x=rcsprite.x;
  rckick.y=rcsprite.y;
  rcleft.x=rcsprite.x;
  rcleft.y=rcsprite.y;
  rcright.x=rcsprite.x;
  rcright.y=rcsprite.y;
  rcbas.x=rcsprite.x;
  rcbas.y=rcsprite.y;
  rcupper.x=rcsprite.x;
  rcupper.y=rcsprite.y;
  rcfor.x=rcsprite.x;
  rcfor.y=rcsprite.y;
  rcspriter.x=rcsprite.x;
  rcspriter.y=rcsprite.y;
  
  /*character animation*/
  left.x = 0 ;
  left.y = 0 ;
  left.h =pusize_haut;
  left.w =pusize_larg ;
  
  right.x = 0;
  right.y= 0;
  right.h=pusize_haut;
  right.w=pusize_larg;
 
  jump.x= 0;
  jump.y= 0;
  jump.h=pusize_haut;
  jump.w=pusize_larg;

  bas.x= 0;
  bas.y= 0;
  bas.h=pusize_haut;
  bas.w=pusize_larg;
  
  ap1.x = 0  ;
  ap1.y = 0 ;
  ap1.h = pusize_haut;
  ap1.w = pusize_larg;

  // character reverse animation
  leftr.x = 1021 - 90 ;
  leftr.y = 0 ;
  leftr.h =pusize_haut;
  leftr.w =pusize_larg ;
  
  rightr.x = 1021 - 90;
  rightr.y= 0;
  rightr.h=pusize_haut;
  rightr.w=pusize_larg;
 
  jump.x= 0;
  jump.y= 0;
  jump.h=pusize_haut;
  jump.w=pusize_larg;

  basr.x= 1021 - 90;
  basr.y= 0;
  basr.h=pusize_haut;
  basr.w=pusize_larg;
  
  apr.x = 1021 - 90  ;
  apr.y = 0 ;
  apr.h = pusize_haut;
  apr.w = pusize_larg;
  
  SDL_Event event;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  setforward();
  setkick();
  setupper();
  setforwardr();
  setkickr();
  setupperr();
  int gameover = 0;
  /* message pump */
  while (!gameover)
  {
    /* look for an event */
    if (SDL_PollEvent(&event)) {
      /* an event was found */
      switch (event.type) {
        /* close button clicked */
      case SDL_QUIT:
	gameover = 1;
	break;
	
      case SDL_KEYUP:
	SDL_Delay(20);
	forward = 0;
	croush=0;
	le = 0;
	ri = 0;
	ap1.x = 0  ;
	ap1.y = 0 ;
	break;
        /* handle the keyboard */
      case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	    break;
	  case SDLK_DOWN:	    
	    croush = 1; 
	    break;
	  case SDLK_RIGHT:
	    forward = 1;
	    pers.right = 1;
	    pers.left = 0;
	    break;
	  case SDLK_LEFT:
	    forward = 1;
	    pers.right = 0;
	    pers.left = 1;
	    break;
	  case SDLK_UP:
	    break;
	  case SDLK_a:
	    le = 1;
	    break;
	  case SDLK_z:
	    ri = 1;
	    break;
	  case SDLK_e:
	    kicks = 1;
	    break;
	  case SDLK_r:
	    uppercut = 1;
	    break;
          case SDLK_q:
	    gameover = 1;
	    break;
          }
          break;

      }
      
    
  }
    
  
    /* draw the background */
    
    SDL_BlitSurface(bg, NULL, screen, NULL);
    if (pers.right == 1)
      {
	if (croush ==1)
	  {
	    rcbas.x=rcsprite.x;
	    rcbas.y=rcsprite.y;
	    SDL_BlitSurface(mov6, &bas , screen, &rcbas );	  
	  }
	else if (le == 1)
	  {
	    rcleft.x=rcsprite.x;
	    rcleft.y=rcsprite.y;
	    SDL_BlitSurface(mov3, &left , screen, &rcleft );
	  }
	else if (ri == 1 )
	  {
	    rcright.x=rcsprite.x;
	    rcright.y=rcsprite.y;
	    SDL_BlitSurface(mov4, &left , screen, &rcright );
	  }
	else if (forward ==1)
	  {
	    sprx = sprx + 35; 
	    rcsprite.x = int (sprx);         //double convertion into int ...
	    rcfor.x=rcsprite.x;
	    rcfor.y=rcsprite.y;
	    SDL_BlitSurface(mov1, &forw[frames] , screen, &rcsprite );
	    SDL_Delay(100);
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		frames = 0 ;
	      }		
	  }
	else if( kicks == 1)
	  {
	    rckick.x=rcsprite.x;
	    rckick.y=rcsprite.y;
	    SDL_BlitSurface(mov2, &kick[frames] , screen, &rckick );
	    SDL_Delay(150);
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		kicks = 0 ;
		frames = 0 ;
	      }	
	  }
	
	else if (uppercut == 1)
	  {
	    rcupper.x=rcsprite.x;
	    rcupper.y=rcsprite.y;
	    SDL_BlitSurface(mov5, &upper[frames] , screen, &rcupper );
	    SDL_Delay(150);
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		uppercut = 0 ;
		frames = 0 ;
	      }
	  }
	else
	  SDL_BlitSurface(sprite, &ap1 , screen, &rcsprite );
      }
    if (pers.left == 1)
      {
	if (croush == 1)
	  {
	    rcbasr.x=rcspriter.x;
	    rcbasr.y=rcspriter.y;
	    SDL_BlitSurface(movr6, &basr , screen, &rcbasr );	  
	  }
	else if (le == 1)
	  {
	    rcleftr.x=rcspriter.x;
	    rcleftr.y=rcspriter.y;
	    SDL_BlitSurface(movr3, &leftr , screen, &rcleftr );
	  }
	else if (ri == 1 )
	  {
	    rcrightr.x=rcspriter.x;
	    rcrightr.y=rcspriter.y;
	    SDL_BlitSurface(movr4, &rightr , screen, &rcrightr );
	  }
	else if (forward == 1)
	  {
	    sprx = sprx - 35; 
	    rcspriter.x = int (sprx);         //double convertion into int ...
	    rcforr.x=rcspriter.x ;
	    rcforr.y=rcsprite.y ;
	    SDL_BlitSurface(movr1, &forwr[frames] , screen, &rcspriter );
	    SDL_Delay(100);
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		frames = 0 ;
	      }		
	  }
	else if( kicks == 1)
	  {
	    rckickr.x=rcsprite.x;
	    rckickr.y=rcsprite.y;
	    SDL_BlitSurface(movr2, &kickr[frames] , screen, &rckickr );
	    SDL_Delay(150);
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		kicks = 0 ;
		frames = 0 ;
	      }	
	  }
	
	else if (uppercut == 1)
	  {
	    rcupperr.x=rcsprite.x;
	    rcupperr.y=rcsprite.y;
	    SDL_BlitSurface(movr5, &upperr[frames] , screen, &rcupperr );
	    SDL_Delay(150);
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		uppercut = 0 ;
		frames = 0 ;
	      }
	  }
	else
	  {
	    SDL_BlitSurface(spriter, &apr , screen, &rcspriter );
	  }
      }
    
    if (sprx >= 950 || spry >= 20 )
      forward = 0;
    
    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }
  
  /* free the background surface */
  SDL_FreeSurface(bg);
  SDL_FreeSurface(sprite);
  /* cleanup SDL */
  SDL_Quit();

  return 0;
}
