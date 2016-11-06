#include "SDL.h"
#define pusize_haut 160
#define pusize_larg 90
#define vit 50
#include "time.h"

double hadx ;
int forward,hadoken,kick;
SDL_Rect ap1 , rcsprite , hadok[5], rchadok;
void setframeshadok()
{
  int i ;
  for (i=0;i=4;i++)
    {
      hadok[i].x += 90 ;
      hadok[i].y = 0;
      hadok[i].h = pusize_haut;
      hadok[i].w = pusize_larg;
    }
}

	  
  
int main ( int argc, char *argv[] )
{
  SDL_Surface *sprite , *temp , *screen, *pow;
  int colorkey;
  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Test", "SDL Test");

  /* create window */
  screen = SDL_SetVideoMode(1047, 480, 0, 0);
  
  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 189 , 206 , 136);
  /* load bitmap to temp surface */
  temp = SDL_LoadBMP("index.bmp");
  SDL_Surface* bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
	
  /* load sprite */
  temp   = SDL_LoadBMP("ryu.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /* load special power*/
  temp   = SDL_LoadBMP("hadoken.bmp");
  pow = SDL_DisplayFormat(temp);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /*charcater position*/
  
  rcsprite.x = 150 ;	
  rcsprite.y = 300 ;
  
  /*character animation*/
  ;

  rchadok.x = 0;
  rchadok.y = 0;
  
  ap1.x = 0  ;
  ap1.y = 0 ;
  ap1.h = pusize_haut;
  ap1.w = pusize_larg;
  
  SDL_Event event;
  setframeshadok();
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
	if (rcsprite.y == 270)
	  {
	    rcsprite.y = 300;
	  }
	ap1.x = 0  ;
	ap1.y = 0 ;
	break;
        /* handle the keyboard */
      case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	    break;
	  case SDLK_DOWN:
	    ap1.x = 95 ;
	    ap1.y = 309 ;
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
	    kick = 1;
	    break;
	  case SDLK_r:
	    hadoken = 1;
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
     if (kick == 1)
      {
	int frame = 0;
	SDL_BlitSurface( pow ,&hadok[frame] , screen, &rchadok );
	if (frame == 4 )
	  kick = 0;
	frame++;
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
