#pragma once
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1260
#define SCREEN_HEIGHT 720

class App{
public:
  App();
  ~App();
  SDL_Renderer *renderer;
  SDL_Window *window;
};