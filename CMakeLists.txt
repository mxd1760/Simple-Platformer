cmake_minimum_required(VERSION 3.10)
project(Platformer_Maps)
include_directories(C:/mingw-w64/12.1.0/include)
add_executable(${CMAKE_PROJECT_NAME} 
  src/main.cpp
  src/app.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}
  mingw32
  SDL2main
  SDL2
  SDL2_image
  SDL2_mixer
  SDL2_ttf
  SDL2_net
)