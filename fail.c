#include "SDL.h"
#define pusize_haut 100
#define pusize_larg 90
#define vit 50
#include "time.h"

double hadx ;
int forward,kicks,uppercut,croush,jum,ri,le;
SDL_Rect ap1 , rcsprite ,left,rcleft,right,rcright,rcfor,forw[3],upper[2],rcupper,kick[2],rckick,jump,rcjump,bas,rcbas;


	  
  
int main ( int argc, char *argv[] )
{
  SDL_Surface *sprite , *temp , *screen, *pow, *mov0,*mov1,*mov2,*mov3,*mov4,*mov5,*mov6;
  int colorkey;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Test", "SDL Test");

  /* create window */
  screen = SDL_SetVideoMode(1047, 480, 0, 0);
  
  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255 , 255 , 255);
  /* load bitmap to temp surface */
  temp = SDL_LoadBMP("index.bmp");
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
  
  SDL_Event event;
  // setframeshadok();
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
	    ap1.x = 348;
	    ap1.y = 163;
	    rcsprite.x = rcsprite.x +  vit;
	    break;
	  case SDLK_LEFT:
	    ap1.x = 85;
	    ap1.y = 157 ;
	    rcsprite.x = rcsprite.x - vit ;
	    break;
	  case SDLK_UP:
	    rcsprite.y = 270;
	    break;
	  case SDLK_a:
	    ap1.x = 100 ;
	    ap1.y = 799 ;
	    break;
	  case SDLK_z:
	    kicks = 1;
	    break;
	  case SDLK_r:
	
	    break;
	  case SDLK_b:
	    ap1.x = 171 ;
	    ap1.y = 308 ;
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

    if (croush ==1)
	{
	  SDL_BlitSurface(mov0, &bas , screen, &rcbas );
	  croush = 0;
	  
	}
    else
    SDL_BlitSurface(sprite, &ap1 , screen, &rcsprite );
    
	
    
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
