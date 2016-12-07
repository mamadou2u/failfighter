#include "SDL.h"
#include "ennemi.h"
#define vit 50




SDL_Rect 
SDL_Surface *move0 , *move1 , *move2 , *move3;
/* setup sprite colorkey and turn on RLE */
colorkey = SDL_MapRGB(screen->format, 255 , 255 , 255);
  /*load ennemy's sprite*/
  temp   = SDL_LoadBMP("Ennemi_Walk.bmp");
  move0 = SDL_DisplayFormat(temp);			
  SDL_SetColorKey(move0, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);

  temp   = SDL_LoadBMP("Ennemi_WalkR.bmp");
  move1 = SDL_DisplayFormat(temp);
  SDL_SetColorKey(move1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);

  temp   = SDL_LoadBMP("Kick.bmp");
  move2 = SDL_DisplayFormat(temp);
  SDL_SetColorKey(move2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);


  temp   = SDL_LoadBMP("Kickr.bmp");
  move3 = SDL_DisplayFormat(temp);
  SDL_SetColorKey(move3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
SDL_Rect  rcspritee,rcspritere,rckicke,forwe[3],forwer[3],forwk[3],forwkr[3];
void setstatic()
{
  rcspritee.x = 150 ;	
  rcspritee.y = 300 ;
  rcspritere.x = 150 ;	
  rcspritere.y = 300 ;
}

void setforwarde()
{
  forwe[0].x=0;
  forwe[0].y=0;
  forwe[0].h=esize_haut;
  forwe[0].w=57;

  forwe[1].x = 57;
  forwe[1].y = 0;
  forwe[1].h = esize_haut;
  forwe[1].w = 116-57;

  forwe[2].x = 116;
  forwe[2].y = 0;
  forwe[2].h = esize_haut;
  forwe[2].w = 187-116;
} 

void setforwardre()
{
  forwer[0].x=209;
  forwer[0].y=0;
  forwer[0].h=esize_haut;
  forwer[0].w=59;
 
  forwer[1].x = 150;
  forwer[1].y = 0;
  forwer[1].h = esize_haut;
  forwer[1].w = 70;

  forwer[2].x = 75;
  forwer[2].y = 0;
  forwer[2].h = esize_haut;
  forwer[2].w = 70;
} 

void setkicke()
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
  forwk[2].w = 102;

}

void setkickre()
{
  forwkr[0].x=265;
  forwkr[0].y=0;
  forwkr[0].h=esize_haut;
  forwkr[0].w=57;
 
  forwkr[1].x = 187;
  forwkr[1].y = 0;
  forwkr[1].h = esize_haut;
  forwkr[1].w = 77;

  forwkr[2].x = 87;
  forwkr[2].y = 0;
  forwkr[2].h = esize_haut;
  forwkr[2].w = 105;

}
void fonckicke()
{
  SDL_BlitSurface(move2, &forwk[frame] , screen, &rcspritee );
  SDL_Delay(150);
  frame = frame + 1;
  if(frame==5)
    {
      
      frame = 0 ;
      rkick=0;
    }
}
void fonckickre()
{
  
  SDL_BlitSurface(move3, &forwkr[frame] , screen, &rcspritere) ;
  SDL_Delay(150);
  frame = frame + 1;
  if(frame==4)
    {
      
      frame = 0 ;
      rkickr=0;
    }
  
}
void foncforwarde ()
{
  
  rcspritee.x =rcspritee.x+vit;         //double convertion into int ...
  rcspritere.x=rcspritee.x;
  SDL_BlitSurface(move0, &forwe[frame] , screen, &rcspritee );
  SDL_Delay(150);
  frame = frame + 1;
  if(frame==2)
    {
      frame = 0 ;
    }
  
}

void foncforwardre()
{
  rcspritere.x =rcspritere.x-vit;         //double convertion into int ...
  rcspritee.x=rcspritere.x;
  SDL_BlitSurface(move1, &forwer[frame] , screen, &rcspritere);
  SDL_Delay(150);
  frame = frame + 1;
  if(frame==2)
    {
      frame = 0 ;
    }
  
}

void foncstatic()
{
  SDL_BlitSurface(move0, &forwer[0] , screen, &rcspritere );
}

void fonstaticr()
{
  SDL_BlitSurface(move1, &forwe[0] , screen, &rcspritee );
}
