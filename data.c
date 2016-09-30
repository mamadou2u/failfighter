#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#define SCREEN_WIDTH  720
#define SCREEN_HEIGHT 540
int gameover; 
void HandleEvent(SDL_Event event)
{
  switch (event.type) 
    {
      /* close button clicked */
    case SDL_QUIT:
      gameover = 1;
      break;
    case SDLK_q:
      gameover = 1;
    }
int main(int argc, char *argv[])

{
  
  SDL_Surface *screen;

  SDL_Init(SDL_INIT_VIDEO); 
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);
  SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
  
  while (!gameover)
    {
      SDL_Event event;
      
      /* look for an event */
      if (SDL_PollEvent(&event)) {
	HandleEvent(event);
      }
      SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    }
  return 0;
      
}
