#include <iostream>
#include "app.h"

using std::cout;
using std::endl;

App::App(){

  int rendererFlags=SDL_RENDERER_ACCELERATED;
  int windowFlags=0;

  if(SDL_Init(SDL_INIT_VIDEO)<0){
    cout << "Couldn't initialize SDL: "<<SDL_GetError()<<endl;
    exit(1);
  }
  window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,windowFlags);

  if(!window){
    cout<<"Failed to open "<<SCREEN_WIDTH << "x"<<SCREEN_HEIGHT<<" winodw: "<<SDL_GetError()<<endl;
    exit(1);
  }
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"linear");

  renderer = SDL_CreateRenderer(window, -1, rendererFlags);

  if(!renderer){
    cout<<"Failed to create renderer: "<<SDL_GetError()<<endl;
    exit(1);
  }
}

App::~App(){
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}