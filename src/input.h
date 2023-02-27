#pragma once

#include <SDL2/SDL.h>

class Input{
public:
  static void do_input();
  static void do_key_down(SDL_KeyboardEvent *event);
  static void do_key_up(SDL_KeyboardEvent *event);
  static int jump;
  static int jump_held;
  static int on_ground;
  static int left;
  static int right;
};