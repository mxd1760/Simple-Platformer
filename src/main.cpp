#include <cstdlib>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include "app.h"
#include "entity.h"
#include "input.h"

using std::vector;

#define SPEED 10
#define GRAVITY 2
#define JUMP_IMPULSE 30
#define TERMINAL_VELOCITY 23

SDL_Texture *loadTexture(App &app, char *filename);
void blit(App &app, SDL_Texture *texture, int x, int y);
void blit(App &app, const Entity &entity);

void process_collisions(Entity &player, std::unique_ptr<vector<Entity>> &blocks,int &velocity_y);

std::unique_ptr<vector<Entity>> loadLevel(vector<SDL_Texture*> textures);
void saveLevel();

int main(int argc,char *args[]){
  App app;
  std::atexit(SDL_Quit);

  char player_sprite_path[] = "../gfx/player.png";
  Entity player{100,100,loadTexture(app,player_sprite_path)};


  char block_sprite_path[] = "../gfx/grass.png";
  SDL_Texture *ground = loadTexture(app,block_sprite_path);
  std::unique_ptr<vector<Entity>> blocks = loadLevel(vector<SDL_Texture*>{ground});

  int velocity_y=0;


  while(true){
    SDL_SetRenderDrawColor(app.renderer,96,128,255,255);
    SDL_RenderClear(app.renderer);

    Input::do_input();
    player.display_rect.x += (Input::right-Input::left)*SPEED;
    if(Input::jump&&Input::on_ground){
      velocity_y=-JUMP_IMPULSE;
      Input::jump=false;
    }else{
      velocity_y+=GRAVITY;
      if(velocity_y>TERMINAL_VELOCITY){
        velocity_y=TERMINAL_VELOCITY;
      }
    }
    Input::on_ground=0;
    player.display_rect.y+=velocity_y;

    process_collisions(player,blocks,velocity_y);

    blit(app,player);
    for(auto g:*blocks){
      blit(app,g);
    }

    SDL_RenderPresent(app.renderer);
    SDL_Delay(16);
  }
  SDL_DestroyTexture(ground);
  SDL_DestroyTexture(player.texture);
}


SDL_Texture *loadTexture(App &app, char *filename){
  SDL_Texture *texture;
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
  texture = IMG_LoadTexture(app.renderer,filename);
  return texture;
}
// void blit(App &app, SDL_Texture *texture, int x, int y){
//   SDL_Rect dest;
//   dest.x = x;
//   dest.y = y;
//   SDL_QueryTexture(texture, NULL,NULL, &dest.w, &dest.h);
//   SDL_RenderCopy(app.renderer, texture, NULL, &dest);
// }
void blit(App &app, const Entity &entity){
  SDL_RenderCopy(app.renderer,entity.texture,NULL,&entity.display_rect);
}

void process_collisions(Entity &player, std::unique_ptr<vector<Entity>> &blocks,int &velocity_y){
  for(auto block:*blocks){
    int top     = block.display_rect.y  + block.display_rect.h  - player.display_rect.y;
    int bottom  = player.display_rect.y + player.display_rect.h - block.display_rect.y;
    int left    = block.display_rect.x  + block.display_rect.w  - player.display_rect.x;
    int right   = player.display_rect.x + player.display_rect.w - block.display_rect.x;
    if(top>0&&bottom>0&&right>0&&left>0){
      if(top<bottom&&top<right&&top<left){
        if(velocity_y<0){
          velocity_y=0;
        }
        player.display_rect.y+=top;
        
      }else if(right<bottom&&right<left){
        player.display_rect.x-=right;
      }else if(left<bottom){
        player.display_rect.x+=left;
      }else{
        player.display_rect.y-=bottom;
        velocity_y=0;
        Input::on_ground = 1;
      }
    }
  }
}


std::unique_ptr<vector<Entity>> loadBoundry(vector<SDL_Texture*> textures){
  std::unique_ptr<vector<Entity>> out{new vector<Entity>};
  for(int i=-1;i<22;i++){
    out->push_back(Entity(i*60,-60,60,60,textures.at(0)));
    out->push_back(Entity(i*60,660,60,60,textures.at(0)));
  }
  for(int i=0;i<11;i++){
    out->push_back(Entity(-60,i*60,60,60,textures.at(0)));
    out->push_back(Entity(1260,i*60,60,60,textures.at(0)));
  }
  return out;
}
std::unique_ptr<vector<Entity>> loadLevel(vector<SDL_Texture*> textures){
  std::ifstream infile{"../levels/lvl1.txt",std::ios::in};
  std::unique_ptr<vector<Entity>> out{loadBoundry(textures)};
  if(!infile.is_open()){
    out->push_back(Entity(100,400,50,50,textures.at(0)));
    out->push_back(Entity(150,400,50,50,textures.at(0)));
    out->push_back(Entity(200,400,50,50,textures.at(0)));
    out->push_back(Entity(200,200,50,50,textures.at(0)));
    return out;
  }
  int row=0;
  while(!infile.eof()){
    std::string line;
    std::getline(infile,line);
    for(int col=0;col<line.length();col++){
      char c = line.at(col);
      if(c=='a'){
        out->push_back(Entity(col*60,row*60,60,60,textures.at(0)));
      }
    } 
    row += 1;            
  }
  infile.close();
  return out;
}
void saveLevel(){
}




