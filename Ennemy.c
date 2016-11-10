#include "SDL.h"
#define esize_haut 90
#define esize_larg 55
#define vit 50
#include "time.h"

SDL_Rect ap1 , rcsprite,rcennemy, rects[8];
int i,frame=0;
void setennemy(SDL_Rect *ap1)
{

  for(i=0;i<8;i++)
    {
      ap1[i].x=ap1[i-1].x + esize_larg;
      ap1[i].y=0;
      ap1[i].w=esize_larg;
      ap1[i].h=esize_haut;
    }
}
int main ( int argc, char *argv[] )
{
  SDL_Surface *sprite , *temp , *screen, *pow, *e1, *e2, *e3;
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
  temp = SDL_LoadBMP("mission1.bmp");
  SDL_Surface* bg = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
	
  /* load sprite */
  temp   = SDL_LoadBMP("Ennemi_Walk.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);

  /*charcater position*/
  
  rcsprite.x = 150 ;	
  rcsprite.y = 300 ;
  
  /*character animation*/

  ap1.x = 0 ;
  ap1.y = 0 ;
  ap1.h = esize_haut;
  ap1.w = esize_larg;
  
  SDL_Event event;
  int gameover = 0;
  setennemy(rects);
  frame++;
  if (frame==7)
    {
      frame=1;
    }
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
            case SDLK_q:
              gameover = 1;
	    break;
          }
          break;

      }
    }
    
    /* draw the background */
    SDL_BlitSurface(bg, NULL, screen, NULL);
    SDL_BlitSurface(sprite,&ap1, screen, &rcsprite );

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
