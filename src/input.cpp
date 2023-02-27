
#include "input.h"
#include <iostream>
using std::cout;
using std::endl;

int Input::jump = 0;
int Input::jump_held = 0;
int Input::on_ground = 0;
int Input::left = 0;
int Input::right =0;

void Input::do_input(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      case SDL_QUIT:
        exit(0);
        break;
      case SDL_KEYDOWN:
        do_key_down(&event.key);
        break;
      case SDL_KEYUP:
        do_key_up(&event.key);
      default:
        break;
    }
  }
}

void Input::do_key_down(SDL_KeyboardEvent *event){
  if(event->repeat==0){
    switch(event->keysym.scancode){
      case SDL_SCANCODE_UP:
      case SDL_SCANCODE_SPACE:
      case SDL_SCANCODE_W:
        jump=1;
        break;
      case SDL_SCANCODE_LEFT:
      case SDL_SCANCODE_A:
        left=1;
        break;
      case SDL_SCANCODE_RIGHT:
      case SDL_SCANCODE_D:
        right=1;
        break;
      default:
        break;
    }
  }
}

void Input::do_key_up(SDL_KeyboardEvent *event){
  if(event->repeat==0){
    switch(event->keysym.scancode){
      case SDL_SCANCODE_UP:
      case SDL_SCANCODE_SPACE:
      case SDL_SCANCODE_W:
        jump=0;
        jump_held=0;
        break;
      case SDL_SCANCODE_LEFT:
      case SDL_SCANCODE_A:
        left=0;
        break;
      case SDL_SCANCODE_RIGHT:
      case SDL_SCANCODE_D:
        right=0;
        break;
      default:
        break;
    }
  }
}