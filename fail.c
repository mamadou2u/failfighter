
#include "SDL.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define vit 50
#define pusize_haut 100
#define pusize_larg 90
#define esize_haut 80
int  frame=0;
#include <math.h>

void MENU (SDL_Surface *screen) //Nouveau menu 
{
        int compteur ; 
	SDL_Surface *temp;
	SDL_Surface *Background, *Arrow;
	SDL_Rect position;
	SDL_Event event;
	//Load Background
	temp = SDL_LoadBMP("logo.bmp");
	Background = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);
      	
	compteur = 1;
	position.x = 0 ;
	position.y = 0  ;

	SDL_BlitSurface (Background,NULL,screen,&position); // background display
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	while( compteur != 0 )
	  {
	    SDL_WaitEvent(&event);
	    if(event.key.keysym.sym == SDLK_SPACE)     
	      {     /*Evenement quit or Continue*/
		compteur = 0;

	      }
	    if(event.key.keysym.sym == SDLK_q)     
	      {
		SDL_Quit();
	      }
	  }
}

double sprx,spry,distance,d,f,dx,df ;
int forward,kicks,kickEnn,kickEnnR,uppercut,croush,jum,ri,le,frames=0,mort,mortE;

SDL_Rect ap1 , rcsprite ,rcspritee,rcspritere,rckicke,forwe[3],forwer[3],forwk[3],forwkr[3],left,rcleft,right,rcright,rcfor,forw[3],forwr[3],upperr[2],upper[2],rcupper,kick[2],rckick,jump,rcjump,bas,rcbas,rcupperr,rckickr,kickr[2],rcforr,rightr,rcrightr,leftr,rcleftr,basr,rcbasr,apr,rcspriter,foe,rcfoe,dead[4],deade[4],deaden[4],deadr[4];
struct personnage 
{
  int pdv;
  int right;//direction du personnage
  int left;
}pers;
/* ***********************************************************************ENEMY ET IA**************************************************************************************************************** */
struct ennemi
{
   int pdv;
   int left;
   int right;
  int avancer;
  int coup;
}enn;
void setstatic()
{
  rcspritee.x = 150 ;	
  rcspritee.y = 300 ;
  rcspritere.x = 650 ;	
  rcspritere.y = 311 ;
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

/* ***************************************************************************************************************************************************************** */

void setdeadr()
{
  dead[0].x=208;
  dead[0].y=0;
  dead[0].h= pusize_haut;
  dead[0].w=48;
  dead[1].x=160;
  dead[1].y=0;
  dead[1].h= pusize_haut;
  dead[1].w=50;
  dead[2].x=88;
  dead[2].y=0;
  dead[2].h= pusize_haut;
  dead[2].w=68;
  dead[3].x=0;
  dead[3].y=0;
  dead[3].h= pusize_haut;
  dead[3].w=70;
}

void setdead()
{
  dead[0].x=0;
  dead[0].y=0;
  dead[0].h= pusize_haut;
  dead[0].w=48;
  dead[1].x=48;
  dead[1].y=0;
  dead[1].h= pusize_haut;
  dead[1].w=50;
  dead[2].x=98;
  dead[2].y=0;
  dead[2].h= pusize_haut;
  dead[2].w=68;
  dead[3].x=166;
  dead[3].y=0;
  dead[3].h= pusize_haut;
  dead[3].w=70;
}

void setmort()
{
  deade[0].x=372;
  deade[0].y=0;
  deade[0].h= pusize_haut;
  deade[0].w=63;
  deade[1].x=261;
  deade[1].y=0;
  deade[1].h= pusize_haut;
  deade[1].w=111;
  deade[2].x=134;
  deade[2].y=0;
  deade[2].h= pusize_haut;
  deade[2].w=127;
  deade[3].x=0;
  deade[3].y=0;
  deade[3].h= pusize_haut;
  deade[3].w=127;
}

void setmortn()
{
  deaden[0].x=0;
  deaden[0].y=0;
  deaden[0].h= pusize_haut;
  deaden[0].w=61;
  deaden[1].x=61;
  deaden[1].y=0;
  deaden[1].h= pusize_haut;
  deaden[1].w=111;
  deaden[2].x=172;
  deaden[2].y=0;
  deaden[2].h= pusize_haut;
  deaden[2].w=127;
  deaden[3].x=300;
  deaden[3].y=0;
  deaden[3].h= pusize_haut;
  deaden[3].w=132;
}

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
  SDL_Surface *sprite , *temp , *screen, *pow, *mov0,*mov1,*mov2,*mov3,*mov4,*mov5,*mov6,*mov7, *movr0,*movr1,*movr2,*movr3,*movr4,*movr5,*movr6,*movr7,*spriter,*enemis,*move0,*move1,*move2,*move3;
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

  /* load sprite */
  temp   = SDL_LoadBMP("static.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /* character movements*/
  temp   = SDL_LoadBMP("jump.bmp");
  mov0  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov0, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // avancer
  temp   = SDL_LoadBMP("avancer.bmp");
  mov1  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // kick
  temp   = SDL_LoadBMP("kick.bmp");
  mov2  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // left
  temp   = SDL_LoadBMP("left.bmp");
  mov3  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // right
  temp   = SDL_LoadBMP("right.bmp");
  mov4  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov4, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // uppercut
  temp   = SDL_LoadBMP("uppercut.bmp");
  mov5  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov5, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // crouch
  temp   = SDL_LoadBMP("bas.bmp");
  mov6  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov6, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // dead animation
  temp   = SDL_LoadBMP("mort.bmp");
  mov7  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(mov7, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  
   /* load sprite */
  temp   = SDL_LoadBMP("staticr.bmp");
  spriter = SDL_DisplayFormat(temp);
  SDL_SetColorKey(spriter, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  /* character movements reverse*/
  temp   = SDL_LoadBMP("jump.bmp");
  movr0  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr0, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // avancer reverse 
  temp   = SDL_LoadBMP("avancerr.bmp");
  movr1  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr1, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // kick reverse 
  temp   = SDL_LoadBMP("kickr.bmp");
  movr2  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr2, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // left reverse 
  temp   = SDL_LoadBMP("leftr.bmp");
  movr3  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr3, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // right reverse
  temp   = SDL_LoadBMP("rightr.bmp");
  movr4  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr4, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // uppercut reverse
  temp   = SDL_LoadBMP("uppercutr.bmp");
  movr5  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr5, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  // crouch reverse
  temp   = SDL_LoadBMP("basr.bmp");
  movr6  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr6, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
  SDL_FreeSurface(temp);
  //dead reverse 
  temp   = SDL_LoadBMP("mortr.bmp");
  movr7  = SDL_DisplayFormat(temp);
  SDL_SetColorKey(movr7, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
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

  rcfoe.x = 800;
  rcfoe.y = 300;
  /*character animation*/

  foe.x = 0;
  foe.y = 0;
  foe.h = 200;
  foe.w = 150 ;
  
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
  
  MENU(screen);
  SDL_Event event;
  setstatic();
  setforwardre();
  setforwarde();
  enn.pdv = 200;
  pers.pdv = 200;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  setforward();
  setkick();
  setkicke();
  setkickre();
  setupper();
  setforwardr();
  setkickr();
  setupperr();
  setdead();
  setdeadr();
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
    if (pers.pdv <= 0)
      mort= 1;
    if (enn.pdv <= 0)
      mortE= 1;
    
    if (pers.right == 1)
      {
	if (croush ==1)
	  {
	    rcbas.x=rcsprite.x;
	    rcbas.y=rcsprite.y;
	    SDL_BlitSurface(mov6, &bas , screen, &rcsprite );	  
	  }
	else if (le == 1)
	  {
	    rcleft.x=rcsprite.x;
	    rcleft.y=rcsprite.y;
	    enn.pdv= enn.pdv-10;
	    SDL_BlitSurface(mov3, &left , screen, &rcsprite );
	  }
	else if (ri == 1 )
	  {
	    rcright.x=rcsprite.x;
	    rcright.y=rcsprite.y;
	    enn.pdv= enn.pdv-10;
	    SDL_BlitSurface(mov4, &left , screen, &rcsprite );
	  }
	else if (forward ==1)
	  {
	   
	    rcsprite.x = rcsprite.x + 25 ;
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
	    enn.pdv= enn.pdv-10;
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
	    enn.pdv= enn.pdv-10;
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		uppercut = 0 ;
		frames = 0 ;
	      }

	  }
	else if (mort == 1)
	  {
	    SDL_BlitSurface(mov7, &dead[frames] , screen,&rcsprite);
	    SDL_Delay(100);
	    frames++;
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
	    enn.pdv= enn.pdv-10;
	    SDL_BlitSurface(movr3, &leftr , screen, &rcleftr );
	  }
	else if (ri == 1 )
	  {
	    rcrightr.x=rcspriter.x;
	    rcrightr.y=rcspriter.y;
	    enn.pdv= enn.pdv-10;
	    SDL_BlitSurface(movr4, &rightr , screen, &rcrightr );
	  }
	else if (forward == 1)
	  {
	    rcsprite.x =  rcsprite.x -25;  //double convertion into int
	    rcspriter.x = rcsprite.x;
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
	    SDL_BlitSurface(movr2, &kickr[frames] , screen, &rcspriter );
	    SDL_Delay(150);
	    enn.pdv= enn.pdv-10;
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
	    SDL_BlitSurface(movr5, &upperr[frames] , screen, &rcspriter );
	    SDL_Delay(150);
	    enn.pdv= enn.pdv-10;
	    frames = frames + 1;
	    if (frames >= 3)
	      {
		uppercut = 0 ;
		frames = 0 ;
	      }
	  }
	else if (mort == 1)
	  {
	    SDL_BlitSurface(movr7, &deadr[frames] , screen,&rcspriter);
	    SDL_Delay(100);
	    frames++;
	  }
	else
	  {
	    SDL_BlitSurface(spriter, &apr , screen, &rcspriter );
	  }
      }
    
    if (sprx >= 950 || spry >= 20 )
      forward = 0;


    /* ****************************************************ENNEMI**************************************************************/
    if((    rcspritere.x-rcsprite.x>125 && mort==0 ))
      {
	rcspritere.x =rcspritere.x-15;         //double convertion into int ...
	rcspritee.x=rcspritere.x;
	SDL_BlitSurface(move1, &forwer[frame] , screen, &rcspritere);
	SDL_Delay(150);
	frame++;
	enn.left =1;
	enn.right=0;
	
	if(frame==2)
	  {
	    frame = 0 ;
	  }
      }
    if(rcspritere.x-rcsprite.x<-125 && mort ==0)      
      {
	rcspritere.x =rcspritere.x+15;        //double convertion into int ...
	rcspritee.x=rcspritere.x;
	SDL_BlitSurface(move0, &forwe [frame] , screen, &rcspritere);
	SDL_Delay(150);
	frame ++ ;
	enn.left =0;
	enn.right=1;
	if(frame==2)
	  {
	    frame = 0 ;
	  }
      }
     /* ****************************************************Fin Walk Ennemi *************************************************************** */ 

    if(rcspritere.x-rcsprite.x>=0 && rcspritere.x-rcsprite.x<=80 && mortE==0)
      {
	printf("%d",pers.pdv);
	SDL_BlitSurface(move3, &forwkr[frame] , screen,&rcspritee);
	SDL_Delay(100);
	frame++;
	if (frame >= 5)
	  {
	    frame = 0;
	    pers.pdv = pers.pdv - 10;
	    SDL_Delay(200);
	  }
	  
      }
    

    
    if(rcspritere.x-rcsprite.x>=-70 && rcspritere.x-rcsprite.x<=0 && mortE==0)
      {
	printf("%d",pers.pdv);
	SDL_BlitSurface(move2, &forwk[frame] , screen,&rcspritee);
	SDL_Delay(100);
	frame++;
	if (frame >= 5)
	  {
	  frame = 0;
	  pers.pdv = pers.pdv - 10;
	  SDL_Delay(200);
	  }
	  
      }




    
      
    /* position personnage de base*/
    if(pers.left==1 && forward==0 && kicks==0 && le==0 && ri == 0 && uppercut==0 && croush==0 && mort ==0)
      SDL_BlitSurface(spriter, &apr , screen, &rcspriter);
    else if(forward==0 && kicks==0 && le==0 && ri == 0 && uppercut==0 && croush==0 && mort == 0)
      SDL_BlitSurface(sprite, &ap1 , screen, &rcsprite );
     else if ( pers.pdv <= 10)
       SDL_BlitSurface(mov7, &dead[3] , screen, &rcsprite );
      



    /*affichage personnage ennemis */
     if( rcspritere.x-rcsprite.x<=125 && rcspritere.x-rcsprite.x>=80 && mortE==0 )
      SDL_BlitSurface(move1, &forwer[0] , screen, &rcspritere );
     else if (rcspritere.x-rcsprite.x>=-125 && rcspritere.x-rcsprite.x<=-70 && mortE==0)
      SDL_BlitSurface(move0, &forwe [0] , screen, &rcspritere );
     else if (mortE==1 && enn.left==1)
       SDL_BlitSurface(moveD, &deade[3] , screen, &rcspritere );
     else if (mortE==1 && enn.left==1)
       SDL_BlitSurface(moveDn, &deaden[3] , screen, &rcspritere );
     printf("mort%d\n",mort);

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
