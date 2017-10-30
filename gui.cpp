#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <assert.h>
using namespace std;

#define SCREEN_W 512
#define SCREEN_H 512
#define SCREEN_NAME "ray"

char screen[512][512][3];

SDL_Window* window;
SDL_Renderer* renderer;

void init_window()
{
  assert(SDL_Init(SDL_INIT_VIDEO) == 0);
  window = SDL_CreateWindow(SCREEN_NAME, 100, 100, SCREEN_W, SCREEN_H, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  for (int i = 0; i< 512; i++)
  for (int j = 0; j< 512; j++)
    screen[i][j][0] = i+j;
}

void destroy_window()
{
  SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow(window);
}

void update_image(void* buffer, int height,int width)
{
  SDL_Surface *myimage = SDL_CreateRGBSurfaceFrom(buffer,width,height,24,width*3,0x0000ff,0x00ff00,0xff0000,0x000000);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, myimage);

  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

  SDL_FreeSurface(myimage);
  SDL_DestroyTexture(texture);
}

void gui_pause()
{
  while (1) {
    // event handling
    SDL_Event e;
    if ( SDL_PollEvent(&e) ) {
      if (e.type == SDL_QUIT)
        break;
      else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
        break;
    }
  }
}
