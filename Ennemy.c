#include "SDL.h"
#define esize_haut 80
#define esize_larg 50
#define nbr_anim 8
#define temps_anim
#define vit 20
#include "time.h"

SDL_Rect ap1 ,apr, rcsprite,rcspriter,rckick,forw[3],forwr[3],forwk[3];
int i,forward,forwardr,rkick,frames=0;
double sprx;
struct ennemi
{
  int right;
  int left;
}en;

void setforward()
{
  forw[0].x=0;
  forw[0].y=0;
  forw[0].h=esize_haut;
  forw[0].w=57;

  forw[1].x = 57;
  forw[1].y = 0;
  forw[1].h = esize_haut;
  forw[1].w = 116-57;

  forw[2].x = 116;
  forw[2].y = 0;
  forw[2].h = esize_haut;
  forw[2].w = 187-116;
} 

void setforwardr()
{
  forwr[0].x=209;
  forwr[0].y=0;
  forwr[0].h=esize_haut;
  forwr[0].w=59;
 
  forwr[1].x = 150;
  forwr[1].y = 0;
  forwr[1].h = esize_haut;
  forwr[1].w = 70;

  forwr[2].x = 75;
  forwr[2].y = 0;
  forwr[2].h = esize_haut;
  forwr[2].w = 70;
} 

void setkick()
{
  forwk[0].x=0;
  forwk[0].y=0;
  forwk[0].h=esize_haut;
  forwk[0].w=70;
 
  forwk[1].x = 73;
  forwk[1].y = 0;
  forwk[1].h = esize_haut;
  forwk[1].w = 77;

  forwk[2].x = 149;
  forwk[2].y = 0;
  forwk[2].h = esize_haut;
  forwk[2].w = 103;

  forwk[3].x=253;
  forwk[3].y=0;
  forwk[3].h=esize_haut;
  forwk[3].w=71;
}

int main ( int argc, char *argv[] )
{
  SDL_Surface *sprite , *temp , *screen,*spriter,*kick;
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

  temp   = SDL_LoadBMP("Ennemi_WalkR.bmp");
  spriter = SDL_DisplayFormat(temp);
  SDL_SetColorKey(spriter, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);

  temp   = SDL_LoadBMP("Kick.bmp");
  kick = SDL_DisplayFormat(temp);
  SDL_SetColorKey(kick, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);

  /*charcater position*/
  
  rcsprite.x = 150 ;	
  rcsprite.y = 300 ;
  
  rcspriter.x = 150 ;	
  rcspriter.y = 300 ;

  rckick.x = rcsprite.x;
  rckick.y = rcsprite.y;

  SDL_Event event;

  setforward();
  setforwardr();
  setkick();
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
	forward=0;
	forwardr=0;
	rkick=0;
	break;
        /* handle the keyboard */
      case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
	  case SDLK_ESCAPE:
	    break;
	  case SDLK_RIGHT:
	    en.right=1;
	    en.left=0;
	    forward=1;
	    break;
	  case SDLK_LEFT:
	    en.left=1;
	    en.right=0;
	    forwardr=1;
	    break;
	  case SDLK_e:
	    rkick=1;
	  case SDLK_q:
              gameover = 1;
	    break;
	    
          }
          break;

      }
    }
    

    /* draw the background */
    SDL_BlitSurface(bg, NULL, screen, NULL);


    if(en.right==1){
      if(forward==1){
	rcsprite.x =rcsprite.x+vit;         //double convertion into int ...
	rcspriter.x=rcsprite.x;
	SDL_BlitSurface(sprite, &forw[frames] , screen, &rcsprite );
	SDL_Delay(150);
	frames = frames + 1;
	if(frames==2)
	  {
	    frames = 0 ;
	  }
      }
      else
	SDL_BlitSurface(sprite, &forw[0] , screen, &rcsprite );
    }
    
    
  
    if(en.left==1){
      if(forwardr==1){
	rcspriter.x =rcspriter.x-vit;         //double convertion into int ...
	rcsprite.x=rcspriter.x;
	SDL_BlitSurface(spriter, &forwr[frames] , screen, &rcspriter );
	SDL_Delay(150);
	frames = frames + 1;
	if(frames==2)
	  {
	    frames = 0 ;
	  }
      }
    }
    else 
      SDL_BlitSurface(spriter, &forwr[0] , screen, &rcspriter );
 
  
  

  if(en.right==0 && en.left==0)
    SDL_BlitSurface(sprite, &forw[0] , screen, &rcsprite );


  

  
  /* update the screen */
  SDL_UpdateRect(screen, 0, 0, 0, 0);
  
  /* free the background surface */
  SDL_FreeSurface(bg);
  SDL_FreeSurface(sprite);
  /* cleanup SDL */
  SDL_Quit();
  
  return 0;
  
  }
}
