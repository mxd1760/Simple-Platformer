
#pragma once
#include <SDL2/SDL_image.h>

class Entity {
  public:
    SDL_Rect display_rect;
    SDL_Texture *texture;
    Entity(SDL_Rect display_rect, SDL_Texture *texture)
    :display_rect{display_rect},texture{texture}{};
    Entity(int x, int y, int sx, int sy,SDL_Texture *texture)
    :texture{texture}{
      display_rect.x=x;
      display_rect.y=y;
      display_rect.w=sx;
      display_rect.h=sy;
    }
    Entity(int x, int y, SDL_Texture *texture)
    :texture{texture}{
      display_rect.x=x;
      display_rect.y=y;
      SDL_QueryTexture(texture,NULL,NULL,&display_rect.w,&display_rect.h);
    }
    bool operator<(const Entity &rhs){
      if(this->display_rect.y<rhs.display_rect.y){
        return true;
      }else if (this->display_rect.y==rhs.display_rect.y){
        return this->display_rect.x<rhs.display_rect.x;
      }else{
        return false;
      }
    }
    bool operator==(const Entity &rhs){
      return this->display_rect.x==rhs.display_rect.x &&
        this->display_rect.y==rhs.display_rect.y &&
        this->display_rect.w==rhs.display_rect.w &&
        this->display_rect.h==rhs.display_rect.h &&
        this->texture==rhs.texture;
    }
};