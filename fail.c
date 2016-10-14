#include "SDL.h"
#define pusize_haut 230
#define pusize_larg 110
#define vit 50





int forward=0;


SDL_Rect ap1 , rcsprite ;
int main ( int argc, char *argv[] )
{
  SDL_Surface *sprite , *temp , *screen;
  int colorkey;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Test", "SDL Test");

  /* create window */
  screen = SDL_SetVideoMode(1047, 480, 0, 0);
  
  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 0 , 0 , 0);

  /* load bitmap to temp surface */
  temp = SDL_LoadBMP("index.bmp");
  SDL_Surface* bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
	
  /* load sprite */
  temp   = SDL_LoadBMP("goku1.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /*charcater position*/
  
  rcsprite.x = 150 ;	
  rcsprite.y = 300 ;
  
  /*character animation*/
  
  ap1.x = 0  ;
  ap1.y = 40 ;
  ap1.h = pusize_haut;
  ap1.w = pusize_larg;
  
  SDL_Event event;
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

        /* handle the keyboard */
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	  case SDLK_RIGHT:
      
	    ap1.x = 360;
	    ap1.y = 40;
	    if (ap1.x > 5 * 110 ){
	      ap1.x = 3 * 110;
	    }
	    rcsprite.x = rcsprite.x +  vit;
	   
	   
	    break;
	  case SDLK_LEFT:
	    forward=1;
	   
	      ap1.x = 480;
	      ap1.y = 30 ;
	      rcsprite.x = rcsprite.x - vit ;
	    break;
	  
	    
	      
            case SDLK_q:
              gameover = 1;
	    break;
          }
          break;
      }
      if ( ap1.x == 480 )
	{
	  ap1.x = 0;
	}
    }
    

    /* draw the background */
    SDL_BlitSurface(bg, NULL, screen, NULL);
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
