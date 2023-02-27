


#include "app.h"
#include <cstdlib>

void do_input();

int main(int argc,char *args[]){
  App app;
  std::atexit(SDL_Quit);

  while(true){
    SDL_SetRenderDrawColor(app.renderer,96,128,255,255);
    SDL_RenderClear(app.renderer);

    do_input();

    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
  }
}

void do_input(){
  SDL_Event event;

  while(SDL_PollEvent(&event)){
    switch(event.type){
      case SDL_QUIT:
        exit(0);
        break;
      default:
        break;
    }
  }
}
